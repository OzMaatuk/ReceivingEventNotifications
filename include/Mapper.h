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
    void addToKey(const std::string& key, const Record& r);
    void setEndTime(const std::string& key, const std::string& pid, const std::string& ts);

public:
    Mapper();
    Mapper(const std::string& sfp);
    virtual ~Mapper();
    virtual void load(std::vector<std::vector<std::string>>& rows);
    virtual void load(const std::string& sfp);
    virtual void add(const std::vector<std::string>& row);
    virtual void start(const std::vector<std::vector<std::string>>& cache);
    virtual void toFile(const std::string& ofp);
    virtual void print();
    virtual std::map<std::string, std::vector<Record>>& getMap();
};

#endif // MAPPER_H