#ifndef TOTALMOBILIZATION_h
#define TOTALMOBILIZATION_h

#include <iostream>
#include "Mobilization.h"

class TotalMobilization : public Mobilization {
public:
    TotalMobilization(std::string state);

    float getIndustryModifier();

    int getNationalMoraleTick();

    std::string getState();

    virtual ~TotalMobilization();
};

#endif
