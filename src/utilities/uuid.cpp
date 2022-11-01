#include "uuid.h"

std::string uuid::generate() {
    std::stringstream ss;
    ss << std::hex;
    for (int i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (int i = 1; i < 13; i++) {
        ss << dis(gen);
        ss << ((i % 4 == 0) ? "-" : "");
    }
    for (int i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}