// Cache.h
#ifndef CACHE_H
#define CACHE_H

#include <glog/logging.h>
#include <queue>
#include <string>
#include <list>
#include <vector>
#include <stdexcept>
#include "MyException.h"
#if defined(_WIN32) || defined(_WIN64)
#include "EventDetails.h"
#endif

/**
 * @class Collect
 * @brief A class for cache object for OS events,
 *
 * This class is responsible to contain OS events that accoured recently.
 */
template <typename T>
class Cache
{
private:
    std::queue<T> cache; // queue to implememnt cache variable
    const T pop();

public:
    Cache();
    virtual ~Cache();
    virtual void add(const T& e);
    virtual const std::queue<T> getAndClear();
    const static std::list<std::vector<std::string>> cacheToStringList(const std::queue<T>& c, std::vector<std::string> (*toStringFunc)(T*));
};

#endif // CACHE_H