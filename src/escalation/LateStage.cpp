#include "LateStage.h"

LateStage::LateStage() : Escalation("LateStage") {}

std::string LateStage::getState() {
    return state;
}

bool LateStage::mobilizationCheck(std::string mobilization) {
    if (mobilization != "PartialMobilization")  //May only demobilize on de-escalation
        return false;
    else
        return true;
}

LateStage::~LateStage() {}



