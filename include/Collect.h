// Config.h
#ifndef COLLECT_H
#define COLLECT_H

#include <future>
#include <conio.h>
#include "Reader.h"
#include "Writer.h"
#include "EventSink.h"
#include "Config.h"
#include "Analyzer.h"

/**
 * @class Collect
 * @brief A class for collecting process events from OS.
 *
 * This class is responsible for async listen and collect start/stop time (OS events) of process,
 * The class will analyze the details collected to produce insight such as malicious activity.
 */
class Collect
{
private:

public:
    Collect();
    ~Collect();
    int main(Config c);
};

#endif // COLLECT_H