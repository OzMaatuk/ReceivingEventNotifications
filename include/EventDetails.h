// EventDetails.h
#ifndef EVENTDETAILS_H
#define EVENTDETAILS_H

// #define WIN32_LEAN_AND_MEAN
// #include <windows.h>
#include <comdef.h>

struct EventDetails
{
    SYSTEMTIME time;
    INT pid;
    BSTR type;
    BSTR name;
};

#endif // EVENTDETAILS_H