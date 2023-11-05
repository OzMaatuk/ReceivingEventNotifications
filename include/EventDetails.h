// EventDetails.h
#ifndef EVENTDETAILS_H
#define EVENTDETAILS_H

#ifdef _WIN32
// #define WIN32_LEAN_AND_MEAN
// #include <windows.h>
#include <comdef.h>

// This struct will represent the details collected for each process event.
struct EventDetails
{
    SYSTEMTIME time;
    INT pid;
    BSTR type;
    BSTR name;

    std::vector<std::string> eventDetailsToStringVector() const
    {
        char *strClass = new char[512];
        wcstombs(strClass, type, 512);
        char *strName = new char[512];
        wcstombs(strName, name, 512);

        std::stringstream strTime;
        strTime << time.wYear
            << ":" << time.wMonth
            << ":" << time.wDay
            << ":" << time.wHour
            << ":" << time.wMinute
            << ":" << time.wSecond
            << ":" << time.wMilliseconds;

        std::vector<std::string> row;
        row.push_back(strTime.str());
        row.push_back(strClass);
        row.push_back(strName);
        row.push_back(std::to_string(pid));
        delete[] strClass;
        delete[] strName;
        return row;
    }

    bool isValid() const
    {
        return true; // TODO
    }
};

#endif // _WIN32
#endif // EVENTDETAILS_H