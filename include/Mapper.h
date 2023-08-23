// Mapper.h
#ifndef MAPPER_H
#define MAPPER_H

#include <json/json.h>
#include <json/writer.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "MapRecord.h"

class Mapper {
    private:
        std::map<std::string, std::vector<Record>> map;
        void printvec(std::vector<std::string> vec);
        void printMap();

    public:
        Mapper();
        ~Mapper();
        void add(std::vector<std::string> row);
        void toFile(std::string fpath);
};

#endif // MAPPER_H