#ifndef WARECONOMY_h
#define WARECONOMY_h

#include <iostream>
#include "Mobilization.h"

class WarEconomy : public Mobilization {
public:

    WarEconomy(std::string state);

    /**
    * Provides the industryModifier of this state as a percentage
    * @return float : The industryModifier for this state.
    */

    float getIndustryModifier();

    /**
    * Provides the NationalMoraleTick of this state as a negative integer
    * @return int : The NationalMorale for this state.
    */

    int getNationalMoraleTick();

    /**
    * Provides functionality to get the state of the object
    * @return The state of the object
    */

    std::string getState();

    virtual ~WarEconomy();
};

#endif
