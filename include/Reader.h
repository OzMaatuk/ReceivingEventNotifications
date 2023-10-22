// Reader.h
#ifndef READER_H
#define READER_H

#include "Mapper.h"

/**
 * @class Reader
 * @brief A class for reading CSV files and storing the data in a list of Map objects.
 *
 * This class is responsible for reading CSV files containing map data and storing the data in a list of Map objects.
 */
class Reader
{
private:
    std::fstream file;
    std::list<std::vector<std::string>> rows;
    bool isValidEventLabel(const std::string& event_label) const;
    bool isValidProcessName(const std::string& process_name) const;
    bool isValidPid(const std::string& pid) const;
    bool isValidRow(const std::vector<std::string>& row) const;


public:
    Reader(const std::string& sfp);
    virtual ~Reader();
    virtual std::list<std::vector<std::string>>& start();
};

#endif // READER_H