#include "EarlyStage.h"

std::string EarlyStage::getState(){
    return "EarlyStage";
}

bool EarlyStage::mobilizationCheck(std::string mobilization){
    if(mobilization=="TotalMobilization")  //Cannot fully mobilize in opening phase of war
     return false;
    else
    return true;
}



