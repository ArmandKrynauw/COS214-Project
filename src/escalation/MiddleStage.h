#ifndef MIDDLESTAGE_H
#define MIDDLESTAGE_H

#include <iostream>

#include "Escalation.h"
/**
 * This class is a ConcreteState in the Escalation State Design Pattern
 * Hierarchy. This state represents the middle stage of the war.
 */
class MiddleStage : public Escalation {
   public:
    /**
     * Provide functionality to create an MiddleStage objects
     *
     * @param stage State of Escalation
     */
    MiddleStage();
    /**
     * Provide functionality to get the state of the escalation object
     *
     * @return std::string Object state
     */
    std::string getState();
    /**
     * Provide functionality to destroy an MiddleStage object
     *
     */
    virtual ~MiddleStage();
};
#endif
