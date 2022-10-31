#ifndef ESCALATION_H
#define ESCALATION_H
#include <iostream>
class EarlyStage;
class MiddleStage;
class LateStage;

class Escalation {
   protected:
        std::string state;
   public:
    /**
     * Provides functionality to check if current escalation level allows
     *  country to change to a certain mobilization level.
     * @return bool : returns true if mobilization allowed
    */
    Escalation(std::string stage);

    Escalation * checkStageOfWar(std::string stage);

    virtual bool mobilizationCheck(std::string mobilization) = 0;

    /**
     * Specifies what state the current state is
     * @return string : The current state
    */


    virtual std::string getState()=0;

    virtual ~Escalation() ;
};
#endif
