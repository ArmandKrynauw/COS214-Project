#include "WarSocket.h"
#include "../war-commands/LoadNextDay.h"
#include "../war-commands/LoadPreviousDay.h"
#include "../war-commands/LoadBattle.h"
#include "../war-commands/RetrieveSimulations.h"
#include "../war-commands/SelectSimulation.h"


WarSocket::WarSocket() {}

void WarSocket::listen() {
    struct mg_mgr mgr;  // Event manager
    mg_mgr_init(&mgr);  // Initialise event manager
    printf("Starting WS listener on %s/websocket\n", s_listen_on);
    mg_http_listen(&mgr, s_listen_on, WSHandler, NULL);  // Create HTTP listener
    for (;;) mg_mgr_poll(&mgr, 1000);             // Infinite event loop
    //std::thread eventThread(EventPoll, &mgr);
    mg_mgr_free(&mgr);
}

void WarSocket::sendMessage(struct mg_connection* c, json data) {
    std::string dump = data.dump();
    mg_ws_send(c, dump.c_str(), dump.size(), WEBSOCKET_OP_TEXT);
}

bool WarSocket::checkMessage(char* message, std::string compare) {
    return strcmp(message, compare.c_str()) == 0;
}

WarCommand* WarSocket::generateWarCommand(struct mg_connection* c, const char* message) {
    json data;

    try {
        data = json::parse(message);

        if (!data.contains("command")) {
            throw WarException("No command was sent", "invalid_command");
        }

        if (data["command"] == "loadNextDay") {
            return new LoadNextDay();
        }
        if (data["command"] == "loadPreviousDay") {
            return new LoadPreviousDay();
        }
        if (data["command"] == "loadDayResults") {
            return new LoadBattle();
        }
        if (data["command"] == "getAvailableSimulations") {
            return new RetrieveSimulations();
        }

        if(data["command"] == "selectSimulation") {
            if (!data.contains("param")) {
                throw WarException("No param was sent", "invalid_param");
            }
            if (!data["param"].is_number_integer()) {
                throw WarException("Param is not an integer", "invalid_param");
            }

            return new SelectSimulation(data["param"]);
        }
    } catch (json::exception& e) {
        json error = {
            {"error", "Could not parse JSON"},
            {"code", "parse_error"}
        };
        sendMessage(c, error);
    } catch (WarException& e) {
        sendMessage(c, e.getJSON());
    }

    return NULL;
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
        struct mg_ws_message* wm = (struct mg_ws_message *) ev_data;
        WarCommand* command = generateWarCommand(c, wm->data.ptr);

        if (!command) {
            std::cout << "Error: Invalid Command" << std::endl;
            sendMessage(c, json{
                {"error", "Invalid command was sent"},
                {"code", "invalid_command"}
            });
            return;
        }

        try {
            command->execute();
            sendMessage(c, command->getResult());
        } catch (WarException& e) {
            std::cout << "Error: Exception in War Engine" << std::endl;
            std::cout << e.getJSON().dump() << std::endl;
            sendMessage(c, e.getJSON());
        }
    }
}