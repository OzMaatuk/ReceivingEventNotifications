#include <chrono>
#include <ctime>
#include <filesystem>
#include <regex>
#include <fcntl.h>
#include <termios.h>
#include <ncurses.h>
#include "Collect.h"
#include "Cache.h"

std::string getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    struct tm *timeinfo = std::localtime(&time_t_now);

    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
}

// Extract the process name from /proc/<PID>/cmdline
std::string getProcessName(const std::string &pid)
{
    std::string cmdlinePath = "/proc/" + pid + "/cmdline";
    std::ifstream cmdlineFile(cmdlinePath);
    if (cmdlineFile)
    {
        std::string cmdline;
        std::getline(cmdlineFile, cmdline);
        size_t pos = cmdline.find('\0'); // Null-terminated strings in cmdline.
        if (pos != std::string::npos)
        {
            cmdline = cmdline.substr(0, pos);
        }
        return cmdline;
    }
    return "";
}

// Function listen for ENTER key press, returns true if been made.
bool waitForKeyPress()
{
    // Open the keyboard file descriptor.
    int fd = open("/dev/stdin", O_RDWR | O_NONBLOCK);

    // Set the keyboard file descriptor to non-blocking.
    fcntl(fd, F_SETFL, O_NONBLOCK);

    // Check for a key press.
    char buf[1];
    int bytesRead = read(fd, buf, sizeof(buf));

    if (bytesRead > 0)
    {
        // A key has been pressed.
        close(fd);
        return true;
    }

    // No key press.
    close(fd);
    return false;
}

// Function to read events from filesystem.
void read_events(Cache<std::vector<std::string>> *event_queue)
{
    DLOG(INFO) << "Starts read_events";

    // Specify the path to the directory containing process information in /proc.
    std::string procPath = "/proc";

    // Keep track of existing processes.
    std::filesystem::directory_iterator it(procPath);
    std::vector<std::string> existingProcesses;

    while (!waitForKeyPress())
    {
        std::vector<std::string> currentProcesses;

        // Iterate through the /proc directory to list running processes.
        for (const auto &entry : std::filesystem::directory_iterator(procPath))
        {
            currentProcesses.push_back(entry.path().filename());
        }

        // Check for new process start events.
        for (const std::string &process : currentProcesses)
        {
            bool isNew = true;
            for (const std::string &existing : existingProcesses)
            {
                if (process == existing)
                {
                    isNew = false;
                    break;
                }
            }

            if (isNew)
            {
                // Process start event.
                std::string pid = process;
                std::string processName = getProcessName(pid);
                std::string timestamp = getCurrentTimestamp();
                event_queue->add(std::vector<std::string>{timestamp, UNIX_PROCESS_START, processName, pid});
                VLOG(1) << timestamp << " - Process " << processName << " (PID: " << pid << ") started." << std::endl;
                // Log the event to a file, if desired.
            }
        }

        // Check for process stop events.
        for (const std::string &existing : existingProcesses)
        {
            bool isGone = true;
            for (const std::string &process : currentProcesses)
            {
                if (existing == process)
                {
                    isGone = false;
                    break;
                }
            }

            if (isGone)
            {
                // Process stop event.
                std::string pid = existing;
                std::string processName = getProcessName(pid);
                std::string timestamp = getCurrentTimestamp();
                event_queue->add(std::vector<std::string>{timestamp, UNIX_PROCESS_END, processName, pid});
                VLOG(1) << timestamp << " - Process " << processName << " (PID: " << pid << ") stopped." << std::endl;
                // Log the event to a file, if desired.
            }
        }

        // Update the list of existing processes.
        existingProcesses = currentProcesses;
    }
    DLOG(INFO) << "Done read_events";
}

Collect::Collect() {}

Collect::~Collect() {}

int Collect::main(Config c)
{
    // Initialize ncurses
    // initscr(); // messingup the logs. when not used, makes WaitForKeyPress() listen only for ENTER press.
    noecho();
    cbreak();

    // Create a queue to store events.
    Cache<std::vector<std::string>> cache;

    // Create a thread to read events.
    DLOG(INFO) << "asyncReadThread";
    auto asyncReadThread = async(std::launch::async, [&cache]()
                                 { return read_events(&cache); });

    Writer *writer = new Writer(c.events_file_path);
    Reader *reader = new Reader(c.events_file_path);
    Mapper *mapper = new Mapper();
    Analyzer *analyzer = new Analyzer(c);

    mapper->load(reader->start());
    // While asyc listening to events in background.
    while (!waitForKeyPress())
    {
        try
        {
            const std::deque<std::vector<std::string>> &tmp = cache.getAndClear();
            if (!tmp.empty())
            {
                auto asyncThread = std::async(std::launch::async, [&mapper, &tmp]()
                                              { return mapper->start(tmp); });
                asyncThread.wait();
                asyncThread = std::async(std::launch::async, [&analyzer, &mapper]()
                                         { return analyzer->start(mapper->getMap()); });
                asyncThread = std::async(std::launch::async, [&writer, &tmp]()
                                         { return writer->start(tmp); });
            }
            usleep(c.sleep_interval * 1000);
        }
        catch (MyException &ex)
        {
            LOG(ERROR) << "My Exception thrown: " << ex.what() << std::endl;
        }
    }

    // Clean up ncurses
    endwin();
    return 0;
}