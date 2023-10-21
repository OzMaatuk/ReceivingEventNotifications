// Cache.h
#ifndef CACHE_H
#define CACHE_H

#include <glog/logging.h>
#include <queue>
#include <string>
#include <list>
#include <vector>
#include "EventDetails.h"

class Cache
{
private:
    std::queue<EventDetails> cache;
    const std::vector<std::string> pop();

public:
    Cache();
    virtual ~Cache();
    virtual void add(const EventDetails& e);
    virtual const std::list<std::vector<std::string>> getAndClear();
};

#endif // CACHE_H