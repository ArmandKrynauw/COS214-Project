#include "WarSocket.h"

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

json WarSocket::validateMessage(struct mg_connection* c, const char* message) {
    json data;

    try {
        data = json::parse(message);
    } catch (json::exception& e) {
        json error = {
            {"error", "Could not parse JSON"},
            {"code", "parse_error"}
        };
        sendMessage(c, error);
        return json{};
    }

    try {
        if (!data.contains("command")) {
            throw WarException("No command was sent", "invalid_command");
        }

        if(data["command"] == "selectSimulation") {
            if (!data.contains("param")) {
                throw WarException("No param was sent", "invalid_param");
            }
            if (!data["param"].is_number_integer()) {
                throw WarException("Param is not an integer", "invalid_param");
            }
        }
    } catch (WarException& e) {
        sendMessage(c, e.getJSON());
        return json{};
    }

    return data;
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
        json data = validateMessage(c, wm->data.ptr);

        if (data.is_null()) {
            return;
        }

        // ================================== API Cases ================================== 

        std::string command = data["command"];
        std::cout << command << std::endl;

        try {
            if (command == "loadNextBattleDay") {
                WarEngine::instance()->loadNextBattleDay();
                sendMessage(c, WarEngine::instance()->getStats());
            }
            else if (command == "loadDayResults") {
                WarEngine::instance()->loadBattleDayResults();
                sendMessage(c, WarEngine::instance()->getStats());
            }
            else if (command == "getAvailableSimulations") {
                sendMessage(c, WarEngine::instance()->getAvailableSimulations());
            }
            else if (command == "selectSimulation") {
                WarEngine::instance()->selectSimulation(data["param"]);
                sendMessage(c, WarEngine::instance()->getStats());
            }
            else{
                std::cout << "Error: Invalid Command - " << command << std::endl;
                const char *str = "{\"error\": \"Invalid command\", \"code\": \"invalid_command\"}";
                mg_ws_send(c, str, strlen(str), WEBSOCKET_OP_TEXT);
            }
        } catch (WarException& e) {
            std::cout << "Error: Exception in War Engine" << std::endl;
            std::string dump = e.getJSON().dump();
            std::cout << dump << std::endl;
            mg_ws_send(c, dump.c_str(), dump.size(), WEBSOCKET_OP_TEXT);
        }
    }
}