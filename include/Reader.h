// Reader.h
#ifndef READER_H
#define READER_H

#include <sstream>
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
    std::fstream sfile;
    Mapper map;
    bool isValidData(std::vector<std::string> row);

public:
    Reader(std::string sfp, std::string ofp);
    ~Reader();
    Mapper &getMap();
    void start();
};

#endif // READER_H