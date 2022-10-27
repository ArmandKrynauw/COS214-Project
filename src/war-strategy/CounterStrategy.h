#ifndef COUNTERSTRATEGY_H
#define COUNTERSTRATEGY_H

#include "WarStrategy.h"

class CounterStrategy : public WarStrategy
{
public:
    CounterStrategy();
    float executeStrategy(WarStrategy* strat);
    ~CounterStrategy();
};

#endif // COUNTERSTRATEGY_H