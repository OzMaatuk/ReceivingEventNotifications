#include <string>

#define START "__InstanceCreationEvent"
#define END "__InstanceDeletionEvent"

struct MapObj
{
    std::string pid;
    std::string start;
    std::string stop;
};