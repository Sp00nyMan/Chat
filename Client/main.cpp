#include "Client.h"
#include <ncurses.h>

int main(int argc, char** argv) {
    if(argc != 3)
    {
        std::cerr << "Usage: client server_ip server_port\n";
        return -1;
    }
    initscr();
    WINDOW* writeWindow = newwin(10, 200, 0, 0);
    WINDOW* chatWindow = newwin(90, 200, 0, 10);
    refresh();

    Client client(argv[1], atoi(argv[2]));
    while(true)
    {
        waddstr(chatWindow, client.recive().c_str());
        std::cout << "> ";
        char buffer[255];
        wgetstr(writeWindow, buffer);
        if(std::string(buffer) == "exit"){
            client.send(std::string("exit"));
            break;
        }
        client.send(std::string(buffer));
        wrefresh(chatWindow);
        wrefresh(writeWindow);
    }
    endwin();
    return 0;
}