#ifndef PARTIALMOBILIZATION_h
#define PARTIALMOBILIZATION_h

#include <iostream>
#include "Mobilization.h"

class PartialMobilization : public Mobilization {
public:

    PartialMobilization(std::string state);

    float getIndustryModifier();

    int getNationalMoraleTick();

    std::string getState();

    virtual ~PartialMobilization();
};

#endif
