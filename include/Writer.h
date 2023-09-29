// Writer.h
#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include "Mapper.h"

/**
 * @class Writer
 * @brief A class for writing event data to a CSV file.
 *
 * This class is responsible for writing event data stored in the EventSink class to a CSV file.
 */
class Writer
{
private:
    std::fstream file;

public:
    Writer(std::string& sfp);
    ~Writer();
    void start(std::vector<std::vector<std::string>>& cache);
    Mapper& getMap();
};

#endif // WRITER_H