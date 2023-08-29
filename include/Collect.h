// Config.h
#ifndef COLLECT_H
#define COLLECT_H

#include <future>
#include "Reader.h"
#include "Writer.h"
#include "EventSink.h"
#include "Config.h"

class Collect
{
private:

public:
    Collect();
    ~Collect();
    int main(Config c);
};

#endif // COLLECT_H