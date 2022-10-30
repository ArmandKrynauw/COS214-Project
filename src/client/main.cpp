#include "../client/client.h"
#include "../engine/WarEngine.h"
#include "WarSocket.h"

int main(int argc, char** argv) {
    bool flag = argc > 1 ? std::string(argv[1]) == "gui" : false;

    Client* client = new Client(flag);
    // client->Run();
    delete client;

    return 0;
}