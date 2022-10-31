#ifndef LATESTAGE_H
#define LATESTAGE_H
#include <iostream>
#include "Escalation.h"

class LateStage : public Escalation {
   public:
     LateStage();
     bool mobilizationCheck(std::string mobilization);
     std::string getState();
     virtual ~LateStage();
};
#endif
