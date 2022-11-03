#ifndef TOTALMOBILIZATION_h
#define TOTALMOBILIZATION_h

#include <iostream>
#include "Mobilization.h"

class TotalMobilization : public Mobilization {
public:
    TotalMobilization(std::string state);

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

    virtual ~TotalMobilization();
};

#endif
