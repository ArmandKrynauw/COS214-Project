#ifndef COUNTERSTRATEGY_H
#define COUNTERSTRATEGY_H

#include "WarStrategy.h"

class CounterStrategy : public WarStrategy {
public:
    CounterStrategy(std::string target);

    /**
     * Executes  a strategy and generates modifiers based on opponents strategy
     * @param strat Opponents strategy to compare with
     * @return float : Modifier to be used in battles
    */

    float executeStrategy(WarStrategy *strat);

    ~CounterStrategy();
};

#endif // COUNTERSTRATEGY_H