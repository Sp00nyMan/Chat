
#include <netinet/in.h>
#include <strings.h>
#include <iostream>

class Server {
    sockaddr_in serverAddress;
    int sock;
public:
    Server(int port)
    {
        bzero((char*)&serverAddress, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddress.sin_port = htons(port);
        sock = socket(serverAddress.sin_family, SOCK_STREAM, 0);
        if(sock < 0) {
            std::cerr << "Error establishing the server socket!\n";
            exit(-1);
        }
        if(bind(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            std::cerr << "Error binding socket to local address\n";
            exit(-1);
        }
    }
};