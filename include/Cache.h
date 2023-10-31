// Cache.h
#ifndef CACHE_H
#define CACHE_H

#include <glog/logging.h>
#include <queue>
#include <string>
#include <list>
#include <vector>
#include <stdexcept>
#include "EventDetails.h"

/**
 * @class Collect
 * @brief A class for cache object for OS events,
 *
 * This class is responsible to contain OS events that accoured recently.
 */
class Cache
{
private:
    std::queue<EventDetails> cache; // queue to implememnt cache variable
    const std::vector<std::string> pop();

public:
    Cache();
    virtual ~Cache();
    virtual void add(const EventDetails& e);
    virtual const std::list<std::vector<std::string>> getAndClear();
};

#endif // CACHE_H