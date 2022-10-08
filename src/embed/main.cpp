#include "../client/client.h"

int main(){
    Client * client = new Client;
    client->Run();
    delete client;
    return 0;
}