#ifndef WARSOCKET_H
#define WARSOCKET_H

#include "mongoose.h"
#include "../engine/WarEngine.h"
#include <iostream>

class Client;

class WarSocket {
public:
    WarSocket();
    /**
     * Provides functionality to start up the websocket and listen
     * for incoming connections.
    */
    void listen();
    /**
     * Provides functionality to send a message over the socket
     * to the web ui.
     * 
     * @param c Connection between the warsocket and the web ui
     * @param data JSON array containing data to be sent to web ui
    */
    static void sendMessage(struct mg_connection *c, nlohmann::json data);
    /**
     * Provides functionality to check a message recieved by the web ui
     * to execute the correct function.
     * 
     * @param message Message that was recieved
     * @param compare Expected message that corresponds with a function
    */
    static bool checkMessage(char* message, std::string compare);

    /**
     * Event handler function that defines connection's behavior.
     * 
     * @param c Connection between the websocket and the web ui 
     * @param ev An event number that is used to tertermine the event
     * @param ev_data Points to specific data for each event 
     * @param fn_data A user defined pointer to the connection
    */
    static void WSHandler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

private:
    const char *s_listen_on = "ws://127.0.0.1:8000";
    const char *s_web_root = ".";

};

#endif
