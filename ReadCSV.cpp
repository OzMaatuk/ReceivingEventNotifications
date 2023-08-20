#include <future>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Map.cpp"

#define OFPATH "map.json"

class ReadCSV {
    private: std::fstream sfile;
    Map map;
    
    public: ReadCSV(std::string fpath) {
        sfile.open(fpath, std::ios::in | std::ios::out | std::ios::app); // , std::ios::in
    }

    ~ReadCSV() {
        sfile.close();
    }

    Map* getMap() {
        return &map;
    }

    void start() {
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
};

int main() {
    printf("Main started");
    std::string sfpath = "events.csv";
    std::string ofpath = "map.json";
    ReadCSV reader = ReadCSV(sfpath);
    reader.start();
    reader.getMap()->toFile(ofpath);
    // auto asyncThread = std::async(std::launch::async, [&reader]() { return reader.start(); });
    // asyncThread.wait();
    getchar();
}