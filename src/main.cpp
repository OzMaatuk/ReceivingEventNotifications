#include "w_main.cpp"
#include "u_main.cpp"
#include "../include/config.h"
#include "../include/exception.h"

int main(int iArgCnt, char ** argv) {
    if (iArgCnt <= 0) throw Exception("Missing config file path as command line argument");
    Config c(argv[0]);
    if (c.os.compare("Windows")) w_main(c, iArgCnt, argv);
    else if (c.os.compare("Unix")) u_main(c, iArgCnt, argv);
    else throw Exception("Cannot determine OS type, accepted values are 'Windows', 'Unix'");
}