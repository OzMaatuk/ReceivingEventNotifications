// Record.h
#ifndef RECORD_H
#define RECORD_H

#include <string>

// This struct will represent an element of the array for each key in the Mapper map. 
struct Record
{
    std::string pid;
    std::string start;
    std::string stop;

    std::string to_string()
    {
        return "PID: " + pid + ", start: " + start + ", stop: " + stop;
    }
};

#endif // RECORD_H