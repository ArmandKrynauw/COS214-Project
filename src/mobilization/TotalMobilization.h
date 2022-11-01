#ifndef TOTALMOBILIZATION_h
#define TOTALMOBILIZATION_h

#include <iostream>
#include "Mobilization.h"

class TotalMobilization : Mobilization {
public:
    float getIndustryModifier();

    int getNationalMoraleTick();

    std::string getState();
};

#endif
