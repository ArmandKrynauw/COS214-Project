#include "../client/client.h"
#include "../engine/WarEngine.h"

int main(int argc, char** argv) {
    bool flag = argc > 1 ? std::string(argv[1]) == "gui" : false;

    Client* client = new Client(true);
    // client->Run();
    delete client;

    return 0;
}