#ifndef LATESTAGE_H
#define LATESTAGE_H
#include <iostream>
#include "Escalation.h"

class LateStage : Escalation {
   public:
     bool mobilizationCheck(std::string mobilization);
     std::string getState();
};
#endif
