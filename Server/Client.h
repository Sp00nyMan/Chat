#include <string>

class Client {
    std::string name;
    long int id;
    int socket;
public:
    Client(const std::string& name, long int id, int socket)
    {
        this->name = name;
        this->id = id;
        this->socket = socket;
    }
};
