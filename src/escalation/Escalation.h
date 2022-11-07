#ifndef ESCALATION_H
#define ESCALATION_H

#include <iostream>

class EarlyStage;
class MiddleStage;
class LateStage;

/**
 * This class is the AbstractState of the Escalation State Design Pattern Hierarchy. This state pattern is used
 * to note the stage of the war. The stage of the war may affect the mobilization of a
 * country as a country may not mobilize to a certain level at certain escalations of the war.
 */
class Escalation {
    protected:
        std::string state;
    public:
        /**
         * Provides functionality to create an Escalation object
         * 
         * @param stage State of Escalation
         */
        Escalation(std::string stage);
        /**
         * Provides functionality to return a new escalation object according 
         * to the current stage of the war.
         * 
         * @return Escalation* New Escalation object for war
        */
        Escalation *checkStageOfWar(std::string stage);
        /**
         * Abstract function to be implemented in the child classes
         * 
         * @return std::string State of war
        */
        virtual std::string getState() = 0;
        /**
         * Provide functionality to destroy an Escalation object
         */
        virtual ~Escalation();
    };

#endif
