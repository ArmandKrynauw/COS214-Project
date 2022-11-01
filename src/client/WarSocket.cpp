#include "WarSocket.h"


void WarSocket::listen() {
    struct mg_mgr mgr;  // Event manager
    mg_mgr_init(&mgr);  // Initialise event manager
    printf("Starting WS listener on %s/websocket\n", s_listen_on);
    mg_http_listen(&mgr, s_listen_on, HTTPHandler, NULL);  // Create HTTP listener
    for (;;) mg_mgr_poll(&mgr, 1000);             // Infinite event loop
    //std::thread eventThread(EventPoll, &mgr);
    mg_mgr_free(&mgr);
}


void WarSocket::CountryUnits(struct mg_connection *c, struct mg_ws_message *message) {
    //const char *test = "bey";

    if (strcmp(message->data.ptr, "GetCountry") == 0) {
        std::string dump = WarEngine::instance()->getCountryUnits().dump();
        int size = dump.size();
        const char *str = dump.c_str();
        mg_ws_send(c, str, size, WEBSOCKET_OP_TEXT);
    }
    std::cout << message->data.ptr << std::endl;
}


void WarSocket::HTTPHandler(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
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
        CountryUnits(c, wm);
    }
    (void) fn_data;
}