#include "AttackStrategy.h"

AttackStrategy::AttackStrategy(std::string target) : WarStrategy(target) {
    this->type = "Attack";
}

float AttackStrategy::executeStrategy(WarStrategy *strat) {
    if (getPlanned()) return 1.5;
    else
        return 1.00;
}

AttackStrategy::~AttackStrategy() {
}