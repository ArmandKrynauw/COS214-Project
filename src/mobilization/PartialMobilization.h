#ifndef PARTIALMOBILIZATION_h
#define PARTIALMOBILIZATION_h
#include <iostream>
#include "Mobilization.h"

class PartialMobilization : Mobilization {
   public:
     float getIndustryModifier();
     int getNationalMoraleTick();
     std::string getState();
};
#endif
