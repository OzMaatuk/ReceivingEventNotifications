// Cache.h
#ifndef CACHE_H
#define CACHE_H

#include <glog/logging.h>
#include <queue>
#include <string>
#include <sstream>
#include "EventDetails.h"

class Cache
{
private:
    std::queue<EventDetails> cache;
    std::vector<std::string> eventDetailsToStringVector(const EventDetails& e);
    std::vector<std::string> pop();

public:
    Cache();
    virtual ~Cache();
    void add(const EventDetails& e);
    std::vector<std::vector<std::string>> getAndClear();
};

#endif // CACHE_H