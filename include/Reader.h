// Reader.h
#ifndef READER_H
#define READER_H

#include "Mapper.h"

/**
 * @class Reader
 * @brief A class for reading CSV files and storing the data in a vector of Map objects.
 *
 * This class is responsible for reading CSV files containing map data and storing the data in a vector of Map objects.
 */
class Reader
{
private:
    std::fstream file;
    bool isValidRow(const std::vector<std::string>& row);

public:
    Reader(const std::string& sfp);
    virtual ~Reader();
    virtual void start(Mapper& m);
};

#endif // READER_H