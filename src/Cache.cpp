#include "Cache.h"

template <class T> Cache<T>::Cache() : cache()
{
    LOG(INFO) << "Creating Cache object";
}

template <class T> Cache<T>::~Cache()
{
    LOG(INFO) << "Destructing Cache object";
}

template <class T> void Cache<T>::add(const T& e)
{
    VLOG(1) << "Event added to Cache object";
    if (!e.isValid()) // checking if the event details are valid
    {
        throw std::runtime_error("Invalid event details");
    }
    cache.push(T(e));
}

template <class T> const std::vector<std::string> Cache<T>::pop()
{
    if (cache.empty()) 
    {
        throw std::runtime_error("Pop called on empty cache"); // throw an exception instead of silently returning
    }
    std::vector<std::string> tmp = std::to_string(cache.front());
    cache.pop();
    return tmp;
}

template <class T> const std::list<std::vector<std::string>> Cache<T>::getAndClear()
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