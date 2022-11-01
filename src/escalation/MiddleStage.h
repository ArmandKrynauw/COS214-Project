#ifndef MIDDLESTAGE_H
#define MIDDLESTAGE_H

#include <iostream>
#include "Escalation.h"

class MiddleStage : public Escalation {
public:
    MiddleStage();

    bool mobilizationCheck(std::string mobilization);

    std::string getState();

    virtual ~MiddleStage();
};

#endif
