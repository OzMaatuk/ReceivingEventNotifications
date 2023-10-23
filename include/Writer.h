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
    std::fstream file; // output file

public:
    Writer(const std::string& sfp);
    virtual ~Writer();
    virtual void start(const std::list<std::vector<std::string>>& cache);
};

#endif // WRITER_H