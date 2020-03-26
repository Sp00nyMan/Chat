
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <cstring>
#include "Client.h"

class Server {
    static std::vector<Client> clients;
    static const sockaddr_in serverAddress;
    static const int socket;
public:
    static void start(int port){
        memset((char*)&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddress.sin_port = htons(port);
        socket = ::socket(serverAddress.sin_family, SOCK_STREAM, 0);
        if(socket < 0) {
            std::cerr << "Error establishing the server socket!\n";
            exit(-1);
        }
        if(bind(socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            std::cerr << "Error binding socket to local address\n";
            exit(-1);
        }
        listen(socket, 5);
        while(true)
        {
            sockaddr_in clientAddress{};
            socklen_t clientAddressSize;
            int clientSocket = accept(socket, (sockaddr*)&clientAddress, &clientAddressSize);
            if(clientSocket < 0)
                break;
            clients.emplace_back("Test", clients.size() + 1, clientSocket);
            //TODO отправить в отдельный поток
        }
    }
};