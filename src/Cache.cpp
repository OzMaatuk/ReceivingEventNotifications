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
        LOG(ERROR) << "Cache pop had failed with message: ";
        LOG(ERROR) << e.what();
        throw MyException(e.what()); 
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

#if defined(_WIN32) || defined(_WIN64)
template <typename T>
const std::list<std::vector<std::string>> Cache<T>::cacheToStringList(const std::queue<T>& c, std::vector<std::string> (*toStringFunc)(T*))
{
    std::queue<T> tmpCache = std::queue<T>(c);
    std::list<std::vector<std::string>> tmp = std::list<std::vector<std::string>>();
    while (!tmpCache.empty())
    {
        // if (!tmp.isValid()) continue; TODO
        tmp.push_back(toStringFunc(&tmpCache.front()));
        tmpCache.pop();
    }
    return tmp;
}
template class Cache<EventDetails>;
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__unix) || defined(__unix__)
template class Cache<std::vector<std::string>>;
#endif