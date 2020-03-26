#include <iostream>
#include "Server.h"
std::vector<Client> Server::clients;
sockaddr_in Server::serverAddress;
int Server::socket;
std::vector<std::string> Server::chatUpdated;

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
