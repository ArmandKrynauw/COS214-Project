#ifndef LATESTAGE_H
#define LATESTAGE_H

#include <iostream>
#include "Escalation.h"

class LateStage : public Escalation {
public:
    LateStage();
    /**
     * Specifies what state the current state is
     * @return string : The current state
    */
    
    std::string getState();

    virtual ~LateStage();
};

#endif
