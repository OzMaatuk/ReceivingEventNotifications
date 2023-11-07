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
    cache.push(T(e));
}

template <typename T>
const T Cache<T>::pop()
{
    try
    {
        T tmp = cache.front();
        cache.pop();
        return tmp;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw MyException("Cache pop had failed with message: " + e.what()); 
    }
}

template <typename T>
const std::queue<T> Cache<T>::getAndClear()
{
    LOG(INFO) << "getAndClear Cache object";
    std::queue<T> tmp = std::queue<T>();
    tmp.swap(cache);
    return tmp;
}

#ifdef _WIN32 // implementation for Windows OS.
template <>
const std::list<std::vector<std::string>> Cache<EventDetails>::cacheToStringList(const std::queue<EventDetails>& c)
{
    std::queue<EventDetails> tmpCache = std::queue<EventDetails>(c);
    std::list<std::vector<std::string>> tmp = std::list<std::vector<std::string>>();
    while (!tmpCache.empty())
    {
        EventDetails tmp = tmpCache.front();
        if (!tmp.isValid()) continue;
        tmp.push_back(tmpCache.front().eventDetailsToStringVector());
        tmpCache.pop();
    }
    return tmp;
}

template class Cache<EventDetails>;
#endif