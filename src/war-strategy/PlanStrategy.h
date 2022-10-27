#ifndef PLANSTRATEGY_H
#define PLANSTRATEGY_H

#include "WarStrategy.h"

class PlanStrategy : public WarStrategy
{
public:
    PlanStrategy();
    float executeStrategy(WarStrategy* strat);
    ~PlanStrategy();
};

#endif // PLANSTRATEGY_H