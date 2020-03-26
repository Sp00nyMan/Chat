
#include <netinet/in.h>
#include <strings.h>
#include <iostream>

class Server {
    sockaddr_in serverAddress;
    int sock;
public:
    Server(int port);
};