#include "../client/client.h"
#include "../engine/WarEngine.h"

int main(){
    std::cout<<"\033[1;32m================= HARDWARE BOOTUP =================\033[0m"<<std::endl;
    Client* client = new Client();
    // client->Run();
    delete client;

    // WarEngine::instance()->setUp("utilities/simulations.json");

    return 0;
}