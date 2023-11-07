#include <unistd.h>
#include <sys/inotify.h>
#include <string>
#include <queue>
#include <ncurses.h>
#include <fcntl.h>
#include <termios.h>
#include "Collect.h"

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

// Function to read events from the inotify instance.
void read_events(std::queue<struct inotify_event> *event_queue)
{
  DLOG(INFO) << "Starts read_events";

  // Initialize inotify instance
  int inotify_fd = inotify_init1(IN_CLOEXEC);

  // Add watch for /proc directory to monitor process events
  int watch_fd = inotify_add_watch(inotify_fd, "/proc", IN_CREATE | IN_DELETE);

  // Create a buffer to store events.
  char buffer[1024];

  // sets the inotify_fd to non-blocking mode using fcntl()
  int flags = fcntl(inotify_fd, F_GETFL);
  fcntl(inotify_fd, F_SETFL, flags | O_NONBLOCK);

  while (!waitForKeyPress())
  {
    // Read events from inotify instance
    int event_size = read(inotify_fd, buffer, sizeof(buffer));

    if (!(event_size < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)))
    {
      // Loop through events
      for (int i = 0; (unsigned)i < event_size / sizeof(struct inotify_event); i++)
      {
        // Get the event
        struct inotify_event *event = (struct inotify_event *)(buffer + i * sizeof(struct inotify_event));

        // Check event type (IN_CREATE for process start, IN_DELETE for process stop)
        if (event->mask & IN_CREATE)
        {
          LOG(INFO) << "Process " << event->name << " started";
        }
        else if (event->mask & IN_DELETE)
        {
          LOG(INFO) << "Process " << event->name << " stopped";
        }
      }
    }
  }

  // Close the inotify instance.
  close(inotify_fd);
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
  std::queue<struct inotify_event> event_queue;

  // Create a thread to read events.
  DLOG(INFO) << "asyncReadThread";
  auto asyncReadThread = async(std::launch::async, [&event_queue]()
                               { return read_events(&event_queue); });

  while (!waitForKeyPress())
  {

    usleep(c.sleep_interval);
  }
  DLOG(INFO) << "Main loop done.";

  // Clean up ncurses
  endwin();
  return 0;
}