#include <iostream>
#include "Client.h"

int main(int argc, char** argv) {
    if(argc != 3)
    {
        std::cerr << "Usage: client server_ip server_port\n";
        return -1;
    }
    Client client(argv[1], atoi(argv[2]));
    while(true)
    {
        std::cout << "> ";
        std::string message;
        std::cin >> message;
        if(message == "exit"){
            client.send("exit");
            break;
        }
        system("clear");
        std::cout << client.recive() << std::endl;
    }
    return 0;
}
