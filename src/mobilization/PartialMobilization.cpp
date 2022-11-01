#include "PartialMobilization.h"

PartialMobilization::PartialMobilization(std::string state) : Mobilization(state){

}


std::string PartialMobilization::getState() {
    return state;
}

float PartialMobilization::getIndustryModifier() {
    return 0.3;
}

int PartialMobilization::getNationalMoraleTick() {
    return -1;
}

PartialMobilization::~PartialMobilization() {}