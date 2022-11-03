#ifndef MIDDLESTAGE_H
#define MIDDLESTAGE_H

#include <iostream>
#include "Escalation.h"

class MiddleStage : public Escalation {
public:
    MiddleStage();

    /**
     * Specifies what state the current state is
     * @return string : The current state
    */
    std::string getState();

    virtual ~MiddleStage();
};

#endif
