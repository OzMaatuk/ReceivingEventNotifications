// Mapper.h
#ifndef MAPPER_H
#define MAPPER_H

#include "Commons.h"

/**
 * @class Mapper
 * @brief A class for managing map object of process details (pid, start, stop)
 *
 * This class is responsible for collecting process events and storing them in map object.
 * The map structure is array of "Record" objects per process.
 */
class Mapper
{
private:
    std::map<std::string, std::list<Record>> map; // Map of process names to records of their start and stop times
    std::string startLabel; // String to contain the label value of event start
    std::string stopLabel; // String to contain the label value of event stop
    void addToKey(const std::string& key, const Record& r);
    void setEndTime(const std::string& key, const std::string& pid, const std::string& ts);

public:
    Mapper();
    Mapper(const std::string& sfp);
    virtual ~Mapper();
    virtual void load(const std::list<std::vector<std::string>>& rows);
    virtual void load(const std::string& sfp);
    virtual void add(const std::vector<std::string>& row);
    virtual void start(const std::list<std::vector<std::string>>& cache);
    virtual void toFile(const std::string& ofp) const;
    virtual void print() const;
    virtual std::map<std::string, std::list<Record>>& getMap();
};

#endif // MAPPER_H