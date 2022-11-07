#include "../client/Client.h"
#include "../engine/WarEngine.h"

int main(int argc, char **argv) {
    bool flag = argc > 1 ? std::string(argv[1]) == "dev" : false;
    
    if (!flag) {
        WarSocket* socket = new WarSocket();
        socket->listen();
    } else {
        Client::instance()->runDevMode();
    }

    return 0;
}