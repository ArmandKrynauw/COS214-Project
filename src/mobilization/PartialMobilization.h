#ifndef PARTIALMOBILIZATION_h
#define PARTIALMOBILIZATION_h

#include <iostream>
#include "Mobilization.h"
/**
 * This class is a ConcreteState for the Mobilization State Design Pattern Hierarchy. This State modifies a countries
 * resources by a factor of 0.3 and sets the morale to -1.
 */
class PartialMobilization : public Mobilization {
    public:
        /**
         * Provide functionality to construct a PartialMobilization object
         * 
         * @param state State in std::string format
         */
        PartialMobilization(std::string state);
        /**
         * Provide functionality to get the industry modifier of this state as a percentage
         * 
         * @return float The industry modifier for this state.
         */
        float getIndustryModifier();
        /**
         * Provides the NationalMoraleTick of this state as a negative integer
         * 
         * @return int The National Morale for this state.
         */
        int getNationalMoraleTick();
        /**
         * Provides functionality to get the state of the object
         * 
         * @return The state of the object
         */
        std::string getState();
        /**
         * Provide functionality to destroy a PartialMobilization object.
         */
        virtual ~PartialMobilization();
};

#endif
