#include "Cache.h"

Cache::Cache() : cache()
{
    LOG(INFO) << "Creating Cache object";
}

Cache::~Cache()
{
    LOG(INFO) << "Destructing Cache object";
}

std::vector<std::string> Cache::eventDetailsToStringVector(EventDetails event)
{
    char *strClass = new char[512];
    wcstombs(strClass, event.type, 512);
    char *strName = new char[512];
    wcstombs(strName, event.name, 512);

    std::stringstream strTime;
    strTime << event.time.wYear
        << ":" << event.time.wMonth
        << ":" << event.time.wDay
        << ":" << event.time.wHour
        << ":" << event.time.wMinute
        << ":" << event.time.wSecond
        << ":" << event.time.wMilliseconds;

    std::vector<std::string> row;
    row.push_back(strTime.str());
    row.push_back(strClass);
    row.push_back(strName);
    row.push_back(std::to_string(event.pid));
    return row;
}

void Cache::add(EventDetails e)
{
    LOG(INFO) << "Event added to Cache object";
    cache.push(e);
}

std::vector<std::string> Cache::pop()
{
    if (cache.empty()) return std::vector<std::string>();
    std::vector<std::string> tmp = eventDetailsToStringVector(cache.front());
    cache.pop();
    return tmp;
}

std::vector<std::vector<std::string>> Cache::getAndClear()
{
    LOG(INFO) << "getAndClear Cache object";
    std::vector<std::vector<std::string>> tmp;
    size_t len = cache.size();
    while (!(--len)) tmp.push_back(pop());
    return tmp;
}