#include <iostream>
#include "Server.h"

int main(int argc, char** argv) {
    if(argc != 2)
    {
        std::cerr << "Usage: server port\n";
        return -1;
    }
    Server::initialize(atoi(argv[1]));
    Server::start();
    return 0;
}
