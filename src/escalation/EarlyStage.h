#ifndef EARLYSTAGE_H
#define EARLYSTAGE_H

#include <iostream>

#include "Escalation.h"
/**
 * This class is a ConcreteState in the Escalation State Design Pattern
 * Hierarchy. This state represents the early stage of the war.
 */
class EarlyStage : public Escalation {
   public:
    /**
     * Provide functionality to create an EarlyStage objects
     *
     * @param stage State of Escalation
     */
    EarlyStage(std::string stage);
    /**
     * Provide functionality to get the state of the escalation object
     *
     * @return std::string Object state
     */
    std::string getState();
    /**
     * Provide functionality to destroy an EarlyStage object
     *
     */
    virtual ~EarlyStage();
};
#endif
