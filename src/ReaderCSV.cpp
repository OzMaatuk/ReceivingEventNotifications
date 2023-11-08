// ReaderCSV.cpp
#include "Reader.h"
#include <stdexcept>

Reader::Reader(const std::string &sfp) : rows()
{
    LOG(INFO) << "Creating Reader object";
    file.open(sfp, std::ios::in);
    if (!file.is_open())
    {
        LOG(ERROR) << "Could not open events file for read " << sfp;
        throw std::runtime_error("Could not open events file for read");
    }
}

Reader::~Reader()
{
    LOG(INFO) << "Destructing Reader object";
    if (file.is_open())
        file.close();
}

bool Reader::isValidEventLabel(const std::string &event_label) const
{
    if (event_label.compare(WIN_PROCESS_START) != 0 && event_label.compare(WIN_PROCESS_END) != 0 && event_label.compare(UNIX_PROCESS_START) != 0 && event_label.compare(UNIX_PROCESS_END) != 0)
        return false;
    return true;
}

bool Reader::isValidProcessName(const std::string &process_name) const
{
    std::regex regex(R"([a-zA-Z0-9]+\.exe$)");
    return std::regex_match(process_name, regex);
}

bool Reader::isValidPid(const std::string &pid) const
{
    std::regex regex("(\\d{4,})");
    return std::regex_match(pid, regex);
}

bool Reader::isValidRow(const std::vector<std::string> &row) const
{
    if (row.empty())
        return false;
    if (!isValidTimestamp(row[0]))
        return false;
    if (!isValidEventLabel(row[1]))
        return false;
    if (!isValidProcessName(row[2]))
        return false;
    if (!isValidPid(row[3]))
        return false;
    return true;
}

// Read Data from file as string vector
std::list<std::vector<std::string>> &Reader::start()
{
    if (!file.is_open())
    {
        LOG(ERROR) << "Could not read CSV file.";
        return rows;
    }
    LOG(INFO) << "Start Reader";
    std::vector<std::string> row;
    std::string line, word;

    try
    {
        while (std::getline(file, line))
        {
            if (file.fail() && !file.eof())
            {
                // check for read error
                LOG(WARNING) << "Error while reading the line.";
                continue;
                // throw std::runtime_error("Error while reading the line.");
            }

            VLOG(1) << "READ_LINE: " << line;
            row.clear();

            std::stringstream s(line);
            // read every column data of a row and
            // store it in a string variable, 'word'
            // add it to the row vector.
            while (std::getline(s, word, ','))
                row.push_back(word);
            if (isValidRow(row))
                rows.push_back(row);
            else
                VLOG(1) << "invalid row: " << line;
        }
    }
    catch (const std::exception &e)
    {
        LOG(ERROR) << "Error while reading the file.";
        LOG(ERROR) << e.what();
        // throw MyException("Error while reading the file.");
    }
    return rows;
}