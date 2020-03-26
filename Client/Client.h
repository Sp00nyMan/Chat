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
    Client(const std::string& serverIP, int serverPort);
    int send(const std::string& message);
    std::string recive();
};