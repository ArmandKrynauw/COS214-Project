#ifndef WARECONOMY_h
#define WARECONOMY_h

#include <iostream>
#include "Mobilization.h"

class WarEconomy : Mobilization {
public:
    float getIndustryModifier();

    int getNationalMoraleTick();

    std::string getState();
};

#endif
