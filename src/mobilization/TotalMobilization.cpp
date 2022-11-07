#include "TotalMobilization.h"

TotalMobilization::TotalMobilization(std::string state) : Mobilization(state){ }

std::string TotalMobilization::getState() {
    return state;
}

float TotalMobilization::getIndustryModifier() {
    return 0.9;
}

int TotalMobilization::getNationalMoraleTick() {
    return -4;
}

TotalMobilization::~TotalMobilization(){ }
