#include "MiddleStage.h"

std::string MiddleStage::getState(){
    return "MiddleStage";
}

bool MiddleStage::mobilizationCheck(std::string mobilization){
    if(mobilization=="PartialMobilization")  //Cannot demobilize at peak of the war
     return false;
    else
    return true;
}



