#include <string>
#include <netinet/in.h>
#include <netdb.h>
#include <libnet.h>
#include <iostream>

class Client {
    std::string serverIP;
    sockaddr_in serverAddress;
    int socket;
public:
    Client(const std::string& serverIP, int serverPort)
    {
        memset((char*)&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        struct hostent* host = gethostbyname(serverIP.c_str());
        serverAddress.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
        serverAddress.sin_port = htons(serverPort);

        socket = ::socket(serverAddress.sin_family, SOCK_STREAM, 0);
        if(socket < 0) {
            std::cerr << "Error establishing the server socket!\n";
            exit(-1);
        }
    }
    int send(const std::string& message) {
        if (connect(socket, (sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
            std::cerr << "Error connecting to socket\n";
            exit(-1);
        }
        int bytesSent = ::send(socket, message.c_str(), message.length(), 0);
        close(socket);
        return bytesSent;
    }
    std::string recive()
    {
        char buffer[255];
        if(connect(socket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
        {
            std::cerr << "Error connecting to socket\n";
            exit(-1);
        }
        recv(socket, buffer, 255, 0);
        close(socket);
        return std::string(buffer);
    }

};