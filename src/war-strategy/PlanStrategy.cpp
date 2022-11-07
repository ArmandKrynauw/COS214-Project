#include "PlanStrategy.h"

PlanStrategy::PlanStrategy(std::string target) : WarStrategy(target) {
    this->type = "Plan";
}

float PlanStrategy::executeStrategy(WarStrategy *strat) {
    setPlanned(true);
    return 1.0;
}

PlanStrategy::~PlanStrategy() {}