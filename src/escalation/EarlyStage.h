#ifndef EARLYSTAGE_H
#define EARLYSTAGE_H

#include <iostream>
#include "Escalation.h"

class EarlyStage : public Escalation {
public:
    EarlyStage(std::string stage);

    bool mobilizationCheck(std::string mobilization);

    std::string getState();

    virtual ~EarlyStage();
};

/**
        * Early :
        Partial or War
          Middle 
        War or Total
          Late
        can only revert, 
        */

#endif
