#include "../client/client.h"

int main(){
    std::cout<<"\033[1;32m================= HARDWARE BOOTUP =================\033[0m"<<std::endl;
    Client * client = new Client;
    client->Run();
    delete client;
    return 0;
}