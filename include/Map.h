// Map.h
#ifndef MAP_H
#define MAP_H

#include <json/json.h>
#include <json/writer.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "Record.h"

class Map {
    private:
        std::map<std::string, std::vector<Record>> map;
        void printvec(std::vector<std::string> vec);
        void printMap();

    public:
        Map();
        ~Map();
        void add(std::vector<std::string> row);
        void toFile(std::string fpath);
        void testJsonCpp();
};

#endif // MAP_H