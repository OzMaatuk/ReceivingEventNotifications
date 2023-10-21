#include <boost/stacktrace.hpp>
#include <cxxabi.h>
#include "Collect.h"

#define NDEBUG

const char* currentExceptionTypeName()
{
    int status;
    return abi::__cxa_demangle(abi::__cxa_current_exception_type()->name(), 0, 0, &status);
}

int main(int iArgCnt, char **argv)
{
    if (iArgCnt <= 1)
        throw MyException("Missing config file path as command line argument");

    try {
        Config c(argv[1]);
        Collect().main(c);
    } catch (std::exception &e) {
        std::cout << boost::stacktrace::stacktrace() << std::endl;
        std::cout << "Type of caught exception is " << currentExceptionTypeName() << std::endl;
        std::cout << e.what() << std::endl;
        throw e;
    }
}