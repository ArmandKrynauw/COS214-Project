#ifndef PLANSTRATEGY_H
#define PLANSTRATEGY_H

#include "WarStrategy.h"

class PlanStrategy : public WarStrategy {
public:
    PlanStrategy(std::string target);

    /**
     * Executes  a strategy and generates modifiers based on opponents strategy
     * @param strat Opponents strategy to compare with
     * @return float : Modifier to be used in battles
    */

    float executeStrategy(WarStrategy *strat);

    ~PlanStrategy();
};

#endif // PLANSTRATEGY_H