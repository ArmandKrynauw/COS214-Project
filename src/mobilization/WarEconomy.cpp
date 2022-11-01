#include "WarEconomy.h"

WarEconomy::WarEconomy(std::string state) : Mobilization(state){

}

std::string WarEconomy::getState() {
    return state;
}

float WarEconomy::getIndustryModifier() {
    return 0.6;
}

int WarEconomy::getNationalMoraleTick() {
    return -2;
}


WarEconomy::~WarEconomy() {

}