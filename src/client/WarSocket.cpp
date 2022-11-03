#include "WarSocket.h"
#include "client.h"

WarSocket::WarSocket() { }

void WarSocket::listen() {
    struct mg_mgr mgr;  // Event manager
    mg_mgr_init(&mgr);  // Initialise event manager
    printf("Starting WS listener on %s/websocket\n", s_listen_on);
    mg_http_listen(&mgr, s_listen_on, WSHandler, NULL);  // Create HTTP listener
    for (;;) mg_mgr_poll(&mgr, 1000);             // Infinite event loop
    //std::thread eventThread(EventPoll, &mgr);
    mg_mgr_free(&mgr);
}

void WarSocket::sendMessage(struct mg_connection *c, json data) {
    std::string dump = data.dump();
    int size = dump.size();
    const char *str = dump.c_str();
    mg_ws_send(c, str, size, WEBSOCKET_OP_TEXT);
}

bool WarSocket::checkMessage(char* message, std::string compare) {
    return strcmp(message, compare.c_str()) == 0;
}

void WarSocket::WSHandler(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_OPEN) {
        // c->is_hexdumping = 1;
    } else if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_http_match_uri(hm, "/websocket")) {
            mg_ws_upgrade(c, hm, NULL);
        } else if (mg_http_match_uri(hm, "/rest")) {
            mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);
        }
    } else if (ev == MG_EV_WS_MSG) {
        // Got websocket frame. Received data is wm->data. Echo it back!
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        //Parse json data recieved
        struct mg_str json = mg_str(wm->data.ptr);
        //Get command
        char *command = mg_json_get_str(json, "$.command");

        
        // ================================== API Cases ================================== 
        //check to see if correct data was given
        if(command){
            std::cout << command << std::endl;
            if (checkMessage(command, "loadNextDay")) {
                sendMessage(c, Client::instance()->loadNextDay());
            }
            else if (checkMessage(command, "loadRoundResults")) {
                sendMessage(c, Client::instance()->loadDayResults());
            }
            else if (checkMessage(command, "getAvailableSimulations")) {
                sendMessage(c, Client::instance()->getAvailableSimulations());
            }
            else if (checkMessage(command, "runNextDay")) {
                sendMessage(c, Client::instance()->runNextDay());
            }
            else if (checkMessage(command, "selectSimulation")) {
                //Wanted to check if param was provided but if is isn't, d is initialized to 0 which is a valid input
                //Will have to figure it out
                double d;
                mg_json_get_num(json, "$.param", &d);
                int param = (int) d;
                std::cout << "Param: " << param << std::endl;
                sendMessage(c, Client::instance()->selectSimulation(param));
            }
            else{
                //A command was given that does not exist
                std::cout << "Error: Invalid command " << command << std::endl;
                const char *str = "{\"error\": \"Invalid command\"}";
                mg_ws_send(c, str, strlen(str), WEBSOCKET_OP_TEXT);
            }
        }
        else{
            //Non valid json was sent to the warengine
            //Might want to use sendMessage funtion, don't know how to create json type string
            //This works
            std::cout << "Error: Check JSON data" << std::endl;
            const char *str = "{\"error\": \"Check JSON data\"}";
            mg_ws_send(c, str, strlen(str), WEBSOCKET_OP_TEXT);
        }
    }
    (void) fn_data;
}