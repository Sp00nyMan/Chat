#include <string>

class Client {
public:
    long int id;
    std::string name;
    int socket;
    Client(const std::string& name, long int id, int socket)
    {
        this->name = name;
        this->id = id;
        this->socket = socket;
    }
};
