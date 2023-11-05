#include "Cache.h"

template <typename T>
Cache<T>::Cache() : cache()
{
    LOG(INFO) << "Creating Cache object";
}

template <typename T>
Cache<T>::~Cache()
{
    LOG(INFO) << "Destructing Cache object";
}

template <typename T>
void Cache<T>::add(const T& e)
{
    VLOG(1) << "Event added to Cache object";
    if (!e.isValid()) // checking if the event details are valid
    {
        throw std::runtime_error("Invalid event details");
    }
    cache.push(T(e));
}

template <typename T>
const T Cache<T>::pop()
{
    if (cache.empty()) 
    {
        throw std::runtime_error("Pop called on empty cache"); // throw an exception instead of silently returning
    }
    T tmp = cache.front();
    cache.pop();
    return tmp;
}

template <typename T>
const std::queue<T> Cache<T>::getAndClear()
{
    LOG(INFO) << "getAndClear Cache object";
    std::queue<T> tmp = std::queue<T>();
    tmp.swap(cache);
    return tmp;
}

template <>
const std::list<std::vector<std::string>> Cache<EventDetails>::cacheToStringList(const std::queue<EventDetails>& c)
{
    std::queue<EventDetails> tmpCache = std::queue<EventDetails>(c);
    std::list<std::vector<std::string>> tmp = std::list<std::vector<std::string>>();
    while (!tmpCache.empty())
    {
        tmp.push_back(tmpCache.front().eventDetailsToStringVector());
        tmpCache.pop();
    }
    return tmp;
}

template class Cache<EventDetails>;