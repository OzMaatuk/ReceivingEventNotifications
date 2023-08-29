#include "w_main.cpp"
// #include "u_main.cpp"
#include <boost/stacktrace.hpp>
#include <cxxabi.h>

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

        // Check if the operating system is Linux.
        #ifdef __linux__
            std::cout << "The operating system is Linux." << std::endl;
            // u_main(c, iArgCnt, argv);
            return 0;
        #endif

        // Check if the operating system is Windows.
        #ifdef _WIN32
            std::cout << "The operating system is Windows." << std::endl;
            w_main(c);
            return 0;
        #endif

        // Check if the operating system is macOS.
        #ifdef __APPLE__
            std::cout << "The operating system is macOS." << std::endl;
            // u_main(c, iArgCnt, argv);
            return 0;
        #endif
    } catch (std::exception &e) {
        boost::stacktrace::stacktrace s = boost::stacktrace::stacktrace();
        std::cout << s << std::endl;
        std::cout << "Type of caught exception is " << currentExceptionTypeName() << std::endl;
        std::cout << e.what() << std::endl;
        throw e;
    }
    
    throw MyException("Cannot determine OS type.");
}