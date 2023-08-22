// Record.h
#ifndef RECORD_H
#define RECORD_H

#include <string>
#define START "__InstanceCreationEvent"
#define END "__InstanceDeletionEvent"

struct Record
{
    std::string pid;
    std::string start;
    std::string stop;
};

#endif // RECORD_H