#include <fstream>
#include "EventSink.h"

class WriteCSV {
    std::ofstream sfile;
    EventSink* pSink;
    
    public: WriteCSV(std::string fpath, EventSink* sink) {
         sfile = std::ofstream(fpath);
         sfile << "timestamp,class,name\n";
         sfile.flush();
         pSink = sink;
    }

    ~WriteCSV() {
        sfile.close();
    }

    void start() {
        // copy cache and clear
        std::list<EventDetails> tmpCache;
        std::copy(pSink->cache.begin(), pSink->cache.end(), std::back_inserter(tmpCache));
        pSink->cache.clear();

        // Export the events list to a CSV file.
        for (auto event : tmpCache)
        {
            char* strClass = new char[512];
            wcstombs(strClass, event.type, 512);
            char* strName = new char[512];
            wcstombs(strName, event.name, 512);
            sfile << event.time.wHour << ":" << event.time.wMinute << ":" << event.time.wSecond << ":" << event.time.wMilliseconds << ", " << strClass << ", " << strName << ", " << event.pid << "\n";
            sfile.flush();
            delete[] strClass;
            delete[] strName;
        }
        // TODO: Can make it more efficient
    }
};