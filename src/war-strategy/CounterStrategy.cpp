#include "CounterStrategy.h"
#include "PlanStrategy.h"
#include "AttackStrategy.h"

CounterStrategy::CounterStrategy(std::string target) : WarStrategy(target) {
    this->type = "Counter";
}

float CounterStrategy::executeStrategy(WarStrategy* strat) {
    if (strat && strat->getType() == "Attack" && strat->getPlanned()){
        return 2.8;
    }
    return 0.7;
}

CounterStrategy::~CounterStrategy() { }