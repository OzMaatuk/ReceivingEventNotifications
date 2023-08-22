// EventDetails.h
#ifndef EVENTDETAILS_H
#define EVENTDETAILS_H

struct EventDetails
{
    SYSTEMTIME time;
    INT pid;
    BSTR type;
    BSTR name;
};

#endif // EVENTDETAILS_H