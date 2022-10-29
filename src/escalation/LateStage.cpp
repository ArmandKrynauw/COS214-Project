#include "LateStage.h"

std::string LateStage::getState(){
    return "LateStage";
}

bool LateStage::mobilizationCheck(std::string mobilization){
    if(mobilization!="PartialMobilization")  //May only demobilize on de-escalation
     return false;
    else
    return true;
}



