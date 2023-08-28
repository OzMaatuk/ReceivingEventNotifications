// ReadCSV.cpp
#include "Reader.h"

Reader::Reader(std::string fpath) {
    sfile.open(fpath, std::ios::in | std::ios::out | std::ios::app); // , std::ios::in
}

Reader::~Reader() {
    sfile.close();
}

Mapper* Reader::getMap() {
    return &map;
}

void Reader::start() {
    // Read the Data from the file
    // as String Vector
    std::vector<std::string> row;
    std::string line, word;

    std::getline(sfile, line);
    while (std::getline(sfile, line)) {
        row.clear();

        // used for breaking words
        std::stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (std::getline(s, word, ',')) {

            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
        map.add(row);
    }
}