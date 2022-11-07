#ifndef WARSOCKET_H
#define WARSOCKET_H

#include <iostream>

#include "../engine/WarEngine.h"
#include "../utilities/json.hpp"
#include "../utilities/mongoose.h"
#include "../war-commands/WarCommand.h"
#include "Client.h"

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
     * @param c Connection between the War Socket and the web ui
     * @param data JSON array containing data to be sent to web ui
     */
    static void sendMessage(struct mg_connection* c, nlohmann::json data);

    /**
     * Provides functionality to check a message received by the web ui
     * to execute the correct function.
     *
     * @param message Message that was received
     * @param compare Expected message that corresponds with a function
     */
    static bool checkMessage(char* message, std::string compare);

    /**
     * Verifies that a param field is set correctly in the JSON command object.
     *
     * @param data JSON object containing command
     * @throws WarException if no paramater is contained
     * @throws WarException if paramater is not an integer
     */
    static void verifyParameter(const json& data);

    /**
     * Provides functionality to verify that a valid JSON message has been
     * received. Will also validate that message has the correct JSON structure.
     * Will return a JSON object if message is validated. Will return a null
     * JSON objected if message is not validated.
     *
     * @return JSON object containing API command
     */
    static void generateWarCommand(struct mg_connection* c,
                                   const char* message);

    /**
     * Event handler function that defines connection's behavior.
     *
     * @param c Connection between the websocket and the web ui
     * @param ev An event number that is used to determine the event
     * @param ev_data Points to specific data for each event
     * @param fn_data A user defined pointer to the connection
     */
    static void WSHandler(struct mg_connection* c, int ev, void* ev_data,
                          void* fn_data);

   private:
    static WarCommand* command;
    const char* s_listen_on = "ws://127.0.0.1:8000";
    const char* s_web_root = ".";
};

#endif
