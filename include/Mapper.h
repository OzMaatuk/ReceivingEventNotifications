// Mapper.h
#ifndef MAPPER_H
#define MAPPER_H

#include "Commons.h"

/*
Map can be cached object, instead of using file.
Here, application can also load data from previous execution.
*/

class Mapper
{
private:
    std::string sfp;
    std::ofstream ofile;
    std::map<std::string, std::vector<Record>> map;
    std::string getStartLabel();
    std::string getStopLabel();
    std::string vectorToString(const std::vector<std::string> &vector);
    void print();
    void addToKey(std::string, Record);
    void setEndTime(std::string key, std::string pid, std::string ts);

public:
    Mapper(std::string spath);
    ~Mapper();
    void add(std::vector<std::string> row);
    void toFile();
    void load();
    std::map<std::string, std::vector<Record>>& getMap();
};

#endif // MAPPER_H