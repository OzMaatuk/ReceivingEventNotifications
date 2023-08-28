#include "w_main.cpp"
// #include "u_main.cpp"
#include <stacktrace>

#define THROW(msg) \
    throw std::runtime_error(std::string(msg) + " in " + __FILE__ + ':' + std::to_string(__LINE__) + ':' + __func__)

int main(int iArgCnt, char **argv)
{
    if (iArgCnt <= 0)
        throw MyException("Missing config file path as command line argument");
    Config c(argv[0]);

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
    throw MyException("Cannot determine OS type.");
}