#include "MiddleStage.h"

MiddleStage::MiddleStage() : Escalation("MiddleStage"){}

std::string MiddleStage::getState(){
    return state;
}

bool MiddleStage::mobilizationCheck(std::string mobilization){
    if(mobilization=="PartialMobilization")  //Cannot demobilize at peak of the war
     return false;
    else
    return true;
}

MiddleStage::~MiddleStage(){}


