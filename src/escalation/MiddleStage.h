#ifndef MIDDLESTAGE_H
#define MIDDLESTAGE_H
#include <iostream>
#include "Escalation.h"

class MiddleStage : Escalation {
   public:
     bool mobilizationCheck(std::string mobilization);
     std::string getState();
};
#endif
