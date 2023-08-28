// Mapper.h
#ifndef MAPPER_H
#define MAPPER_H

#include <glog/logging.h>
#include <json/json.h>
#include <json/writer.h>
#include <vector>
#include <map>
#include <fstream>
#include "MapRecord.h"
#include "MyException.h"

/*
Map can be cached object, instead of using file.
Here, application can also load data from previous execution.
*/

class Mapper
{
private:
    std::string ofp;
    std::ofstream ofile;
    std::map<std::string, std::vector<Record>> map;
    std::string getStartLabel();
    std::string getStopLabel();
    std::string vectorToString(const std::vector<std::string> &vector);
    void print();
    void addToKey(std::string, Record);
    void setEndTime(std::string key, std::string pid, std::string ts);

public:
    Mapper(std::string fpath);
    ~Mapper();
    void add(std::vector<std::string> row);
    void toFile();
    void load();
};

#endif // MAPPER_H