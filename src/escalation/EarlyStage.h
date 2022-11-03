#ifndef EARLYSTAGE_H
#define EARLYSTAGE_H

#include <iostream>
#include "Escalation.h"

class EarlyStage : public Escalation {
public:
    EarlyStage(std::string stage);

    /**
     * Specifies what state the current state is
     * @return string : The current state
    */
    std::string getState();

    virtual ~EarlyStage();
};

#endif
