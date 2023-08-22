// WriteCSV.h
#ifndef WRITECSV_H
#define WRITECSV_H

#include <fstream>
#include "EventSink.h"

/**
 * @class WriteCSV
 * @brief A class for writing event data to a CSV file.
 *
 * This class is responsible for writing event data stored in the EventSink class to a CSV file.
 */
class WriteCSV {
    private:
        std::ofstream sfile;
        EventSink* pSink;
    
    public:
        WriteCSV(std::string fpath, EventSink* sink);
        ~WriteCSV();
        void start();
};

#endif // WRITECSV_H