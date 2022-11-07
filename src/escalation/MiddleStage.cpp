#include "MiddleStage.h"

MiddleStage::MiddleStage() : Escalation("MiddleStage") {}

std::string MiddleStage::getState() {
    return state;
}

MiddleStage::~MiddleStage() {}


