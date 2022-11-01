#include "EarlyStage.h"


EarlyStage::EarlyStage(std::string stage) : Escalation(stage) {}

std::string EarlyStage::getState() {
    return state;
}

bool EarlyStage::mobilizationCheck(std::string mobilization) {
    if (mobilization == "TotalMobilization")  //Cannot fully mobilize in opening phase of war
        return false;
    else
        return true;
}

EarlyStage::~EarlyStage() {}



