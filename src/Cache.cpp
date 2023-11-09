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
void Cache<T>::add(const T &e)
{
    try
    {
        cache.push_back(T(e));
    }
    catch (const std::exception &e)
    {
        LOG(WARNING) << "Add had failed with message: ";
        LOG(WARNING) << e.what();
        // throw MyException(e.what());
    }
    VLOG(1) << "Event added to Cache object";
}

template <typename T>
const T Cache<T>::pop()
{
    try
    {
        T tmp = cache.front();
        cache.pop_front();
        return tmp;
    }
    catch (const std::exception &e)
    {
        LOG(WARNING) << "Pop had failed with message: ";
        LOG(WARNING) << e.what();
        throw MyException(e.what());
    }
}

template <typename T>
const std::deque<T> Cache<T>::getAndClear()
{
    LOG(INFO) << "getAndClear Cache object";
    std::deque<T> tmp = std::deque<T>();
    try
    {
        tmp.swap(cache);
    }
    catch (const std::exception &e)
    {
        LOG(WARNING) << "getAndClear had failed with message: ";
        LOG(WARNING) << e.what();
        // throw MyException(e.what());
    }
    return tmp;
}

#if defined(_WIN32) || defined(_WIN64)
template <typename T>
const std::deque<std::vector<std::string>> Cache<T>::cacheToStringList(const std::deque<T> &c, std::vector<std::string> (*toStringFunc)(T *))
{
    try
    {
        std::deque<T> tmpCache = std::deque<T>(c);
        std::deque<std::vector<std::string>> tmp = std::deque<std::vector<std::string>>();
        while (!tmpCache.empty())
        {
            // if (!tmp.isValid()) continue; TODO
            tmp.push_back(toStringFunc(&tmpCache.front()));
            tmpCache.pop_front();
        }
        return tmp;
    }
    catch (const std::exception &e)
    {
        LOG(ERROR) << "Failed in cacheToStringList() with message: ";
        LOG(ERROR) << e.what();
        throw MyException(e.what());
    }
}
template class Cache<EventDetails>;
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__unix) || defined(__unix__)
template class Cache<std::vector<std::string>>;
#endif