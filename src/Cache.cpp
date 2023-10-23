#include "Cache.h"

Cache::Cache() : cache()
{
    LOG(INFO) << "Creating Cache object";
}

Cache::~Cache()
{
    LOG(INFO) << "Destructing Cache object";
}

void Cache::add(const EventDetails& e)
{
    VLOG(1) << "Event added to Cache object";
    cache.push(EventDetails(e));
}

const std::vector<std::string> Cache::pop()
{
    if (cache.empty()) return std::vector<std::string>(); // TODO: Not good.
    std::vector<std::string> tmp = cache.front().eventDetailsToStringVector();
    cache.pop();
    return tmp;
}

const std::list<std::vector<std::string>> Cache::getAndClear()
{
    LOG(INFO) << "getAndClear Cache object";
    std::list<std::vector<std::string>> tmp = std::list<std::vector<std::string>>();
    size_t len = cache.size();
    while (len > 0)
    {
        tmp.push_back(pop());
        len--;
    }
    return tmp;
}