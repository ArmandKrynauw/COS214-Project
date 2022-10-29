#ifndef EARLYSTAGE_H
#define EARLYSTAGE_H
#include <iostream>
#include "Escalation.h"

class EarlyStage : Escalation {
   public:
     bool mobilizationCheck(std::string mobilization);
     std::string getState();
};
#endif
