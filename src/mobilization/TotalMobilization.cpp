#include "TotalMobilization.h"

std::string TotalMobilization::getState(){
    return "TotalMobilization";
}

float TotalMobilization::getIndustryModifier(){
    return 0.9;
}

int TotalMobilization::getNationalMoraleTick(){
    return -4;
}
