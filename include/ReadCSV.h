// ReadCSV.h
#ifndef READCSV_H
#define READCSV_H

#include <sstream>
#include "Map.h"

/**
 * @class ReadCSV
 * @brief A class for reading CSV files and storing the data in a vector of Map objects.
 *
 * This class is responsible for reading CSV files containing map data and storing the data in a vector of Map objects.
 */
class ReadCSV {
    private:
        std::fstream sfile;
        Map map;
    
    public:
        ReadCSV(std::string fpath);
        ~ReadCSV();
        Map* getMap();
        void start();
};

#endif // READCSV_H