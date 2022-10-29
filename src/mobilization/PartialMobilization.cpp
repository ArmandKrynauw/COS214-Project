#include "PartialMobilization.h"

std::string PartialMobilization::getState(){
    return "PartialMobilization";
}

float PartialMobilization::getIndustryModifier(){
    return 0.3;
}

int PartialMobilization::getNationalMoraleTick(){
    return -1;
}

PartialMobilization::~PartialMobilization(){}