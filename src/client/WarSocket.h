#ifndef WARSOCKET_H
#define WARSOCKET_H

#include "mongoose.h"
#include "../engine/WarEngine.h"
#include <iostream>

class Client;

class WarSocket {
public:
    WarSocket();
    void listen();

    static void sendMessage(struct mg_connection *c, nlohmann::json data);
    static bool checkMessage(char* message, std::string compare);
    static void HTTPHandler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

private:
    const char *s_listen_on = "ws://127.0.0.1:8000";
    const char *s_web_root = ".";

};

#endif
