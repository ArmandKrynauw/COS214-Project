#ifndef MOBILIZATION_h
#define MOBILIZATION_h

#include <iostream>
#include "../utilities/WarException.h"
class WarEconomy;
class PartialMobilization;
class TotalMobilization;

/**
 * This class is the AbstractState for the Mobilization State Design Pattern Hierarchy. This State pattern modifies
 * countries' resources by an increase or decrease depending on the mobilization state of the country.
 */
class Mobilization {
    protected:
    std::string state;
    public:
        /**
         * Provide functionality to construct a Mobilization object
         * 
         * @param state State in std::string format
         */
        Mobilization(std::string state);
        /**
         * Provide functionality to check the current war escalation and the new Mobilization of
         * the country and set the new Mobilization of the country if the escalation allows it.
         * 
         * @param warState Current escalation of the war
         * @param newMobilization New mobilization that country wants to enter
         * @return Mobilization* New or current mobilization of country
         */
        Mobilization * checkWarState(std::string warState, std::string newMobilization);
        /**
         * Abstract function to be implemented in the child classes.
         * 
         * @return float The industry modifier for this state.
         */
        virtual float getIndustryModifier() = 0;
        /**
         * Abstract function to be implemented in the child classes.
         * 
         * @return int The National Morale for this state.
         */
        virtual int getNationalMoraleTick() = 0;
        /**
         * Abstract function to be implemented in the child classes.
         * 
         * @return string The state of the object
         */
        virtual std::string getState() = 0;
        /**
         * Provides functionality to set the state of the current object
         * 
         * @param state The new state of the object
         */
        void setState(std::string state);
        /**
         * Provide functionality to destroy a Mobilization object.
         */
        virtual ~Mobilization();
};
#endif
