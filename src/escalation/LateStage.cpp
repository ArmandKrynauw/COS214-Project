#include "LateStage.h"

LateStage::LateStage() : Escalation("LateStage") {}

std::string LateStage::getState() {
    return state;
}

LateStage::~LateStage() {}
