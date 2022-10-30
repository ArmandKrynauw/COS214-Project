#ifndef WARSOCKET_H
#define WARSOCKET_H
#include "mongoose.h"
#include <iostream>

class WarSocket {
    public:
        void operator()();
        static void messageRecieved(struct mg_connection *c, struct mg_ws_message *message);
        static void HTTPHandler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
    private:
        const char *s_listen_on = "ws://127.0.0.1:8000";
        const char *s_web_root = ".";

};
#endif
