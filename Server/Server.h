
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <cstring>
#include "Client.h"

class Server {
    static std::vector<Client> clients;
    static sockaddr_in serverAddress;
    static int socket;
    static std::vector<std::string> chatUpdated;

    static int reciveMessage(const Client& client)
    {
        std::cout << "Reciving\n";
        char buffer[255];
        if(try_recv(client.socket, buffer, 255, 0) == 0)
            return 0;
        if(buffer == "exit")
            return -1;
        chatUpdated.push_back(client.name + ": " + buffer);
        std::cout << "Recived\n";
        return 0;
    }
    static void sendMessage(const Client& client)
    {
        std::string bufferConsole;
        for (int i = 0; i < chatUpdated.size(); ++i) {
            bufferConsole += chatUpdated[i] + "\n";
        }
        send(client.socket, bufferConsole.c_str(), bufferConsole.length(), 0);
    }

public:
    static void initialize(int port)
    {
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
    }

    static void start(){
        listen(socket, 5);
        std::cout << "Started!!!\n";
        while(true)
        {
            std::cout << "CYCLE" << std::endl;
            sockaddr_in clientAddress{};
            socklen_t clientAddressSize;
            int clientSocket = accept(socket, (sockaddr*)&clientAddress, &clientAddressSize);
            std::cout << "accepted\n";
            if(clientSocket >= 0)
                clients.emplace_back("Test", clients.size() + 1, clientSocket);
            for (int i = 0; i < clients.size(); ++i) {
                if(reciveMessage(clients[i]) != -1)
                    continue;
                clients.erase(clients.begin() + i);
            }
            for (int i = 0; i < clients.size(); ++i) {
                sendMessage(clients[i]);
            }
            chatUpdated.clear();
        }
    }
};