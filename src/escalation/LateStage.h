#ifndef LATESTAGE_H
#define LATESTAGE_H

#include <iostream>
#include "Escalation.h"
/**
 * This class is a ConcreteState in the Escalation State Design Pattern Hierarchy. This state represents the late
 * stage of the war.
 */
class LateStage : public Escalation {
    public:
        /**
         * Provide functionality to create an LateStage objects
         * 
         * @param stage State of Escalation
         */
        LateStage();
        /**
         * Provide functionality to get the state of the escalation object
         * 
         * @return std::string Object state
        */
        std::string getState();
        /**
         * Provide functionality to destroy an LateStage object
         * 
         */
        virtual ~LateStage();
};
#endif
