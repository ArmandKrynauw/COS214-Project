#include "EarlyStage.h"


EarlyStage::EarlyStage(std::string stage) : Escalation(stage) {}

std::string EarlyStage::getState() {
    return state;
}


EarlyStage::~EarlyStage() {}



