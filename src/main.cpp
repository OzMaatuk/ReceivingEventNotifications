#include "w_main.cpp"
#include "u_main.cpp"
#include "../include/config.h"
#include "../include/exception.h"

int main(int iArgCnt, char ** argv) {
    if (iArgCnt <= 0) throw Exception("Missing config file path as command line argument");
    Config c(argv[0]);

    // Check if the operating system is Linux.
    #ifdef __linux__
        std::cout << "The operating system is Linux." << std::endl;
        u_main(c, iArgCnt, argv);
        return 0;
    #endif

    // Check if the operating system is Windows.
    #ifdef _WIN32
        std::cout << "The operating system is Windows." << std::endl;
        w_main(c, iArgCnt, argv);
        return 0;
    #endif

    // Check if the operating system is macOS.
    #ifdef __APPLE__
        std::cout << "The operating system is macOS." << std::endl;
        u_main(c, iArgCnt, argv);
        return 0;
    #endif
    throw Exception("Cannot determine OS type.");
}