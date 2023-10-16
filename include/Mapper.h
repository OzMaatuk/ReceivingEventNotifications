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
    std::map<std::string, std::vector<Record>> map;
    std::string startLabel;
    std::string stopLabel;
    void addToKey(std::string, Record);
    void setEndTime(std::string key, std::string pid, std::string ts);
    void load(std::string sfp);

public:
    Mapper();
    Mapper(std::string sfp);
    virtual ~Mapper();
    virtual void print();
    virtual void toFile(std::string ofp);
    virtual void start(std::vector<std::vector<std::string>>& cache);
    virtual void add(std::vector<std::string> row);
    std::map<std::string, std::vector<Record>>& getMap();
};

#endif // MAPPER_H