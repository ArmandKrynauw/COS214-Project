#ifndef ATTACKSTRATEGY_H
#define ATTACKSTRATEGY_H

#include "WarStrategy.h"

class AttackStrategy : public WarStrategy {
public:
    AttackStrategy(std::string target);
    /**
     * Executes  a strategy and generates modifiers based on opponents strategy
     * @param strat Opponents strategy to compare with
     * @return float : Modifier to be used in battles
    */

    float executeStrategy(WarStrategy *strat);

    ~AttackStrategy();
};

#endif // ATTACKSTRATEGY_H