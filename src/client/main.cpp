#include "../client/client.h"
#include "../engine/WarEngine.h"

int main(int argc, char **argv) {
    bool flag = argc > 1 ? std::string(argv[1]) == "gui" : false;
    flag = true;
    
    if (flag) {
        Client::instance()->runGUIMode();
        WarSocket* socket = new WarSocket();
        socket->listen();
    } else {
        Client::instance()->runTerminalMode();
    }


    return 0;
}