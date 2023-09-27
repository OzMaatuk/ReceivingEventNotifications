// Writer.h
#ifndef WRITER_H
#define WRITER_H

#include <glog/logging.h>
#include <fstream>
#include "EventSink.h"

/**
 * @class Writer
 * @brief A class for writing event data to a CSV file.
 *
 * This class is responsible for writing event data stored in the EventSink class to a CSV file.
 */
class Writer
{
private:
    std::ofstream sfile;
    std::fstream fileReader;
    EventSink *pSink;

public:
    Writer(std::string fpath, EventSink *sink);
    ~Writer();
    void start();
};

#endif // WRITER_H