#ifndef WARECONOMY_h
#define WARECONOMY_h

#include <iostream>
#include "Mobilization.h"

class WarEconomy : public Mobilization {
public:

    WarEconomy(std::string state);

    float getIndustryModifier();

    int getNationalMoraleTick();

    std::string getState();

    virtual ~WarEconomy();
};

#endif
