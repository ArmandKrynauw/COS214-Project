#ifndef MOBILIZATION_h
#define MOBILIZATION_h

#include <iostream>
#include "../utilities/WarException.h"
class WarEconomy;
class PartialMobilization;
class TotalMobilization;

class Mobilization {
    protected:
    std::string state;

    public:
        Mobilization(std::string state);

        Mobilization * checkWarState(std::string warState, std::string newMobilization);

        /**
        * Provides the industryModifier of this state as a percentage
        * @return float : The industryModifier for this state.
        */
        virtual float getIndustryModifier() = 0;

        /**
        * Provides the NationalMoraleTick of this state as a negative integer
        * @return int : The NationalMorale for this state.
        */
        virtual int getNationalMoraleTick() = 0;

        /**
        * Specifies what state the current state is
        * @return string : The current state
        */
        virtual std::string getState() = 0;

        /**
        * Provides functionality to set the state of the current object
        * @param state The state of the object
        */
        void setState(std::string state);

        virtual ~Mobilization();
};

#endif
