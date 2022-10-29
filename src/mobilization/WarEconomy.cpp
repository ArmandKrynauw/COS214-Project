#include "WarEconomy.h"

std::string WarEconomy::getState(){
    return "WarEconomy";
}

float WarEconomy::getIndustryModifier(){
    return 0.6;
}

int WarEconomy::getNationalMoraleTick(){
    return -2;
}
