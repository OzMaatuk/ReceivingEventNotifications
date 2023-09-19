// WriterCSV.cpp
#include "Writer.h"

Writer::Writer(std::string fpath, EventSink *sink)
{
    pSink = sink;
    std::string line;
    fileReader = std::fstream(fpath);
    std::getline(fileReader, line);
    fileReader.close();
    sfile = std::ofstream(fpath);
    if (line.compare("timestamp,class,name\n") != 0)
    {
        sfile << "timestamp,class,name\n";
        sfile.flush();
    }
}

Writer::~Writer()
{
    sfile.close();
}

void Writer::start()
{
    // Copy cache and clear
    std::list<EventDetails> tmpCache;
    std::copy(pSink->cache.begin(), pSink->cache.end(), std::back_inserter(tmpCache));
    pSink->cache.clear();

    // Export the events list to a CSV file.
    for (auto event : tmpCache)
    {
        char *strClass = new char[512];
        wcstombs(strClass, event.type, 512);
        char *strName = new char[512];
        wcstombs(strName, event.name, 512);
        sfile // << event.time.wYear
            // << ":"
            // << event.time.wMonth
            // << ":"
            // << event.time.wDay
            // << ":"
            << event.time.wHour
            << ":" 
            << event.time.wMinute
            << ":"
            << event.time.wSecond
            << ":"
            << event.time.wMilliseconds
            << ","
            << strClass
            << ","
            << strName
            << ","
            << event.pid
            << "\n";
        sfile.flush();
        delete[] strClass;
        delete[] strName;
    }
}