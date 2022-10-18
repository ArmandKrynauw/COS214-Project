#ifndef PLANSTRATEGY_H
#define PLANSTRATEGY_H

#include "WarStrategy.h"

class PlanStrategy : public WarStrategy
{
public:
    PlanStrategy();
    void planOfAction();
    ~PlanStrategy();
};

#endif // PLANSTRATEGY_H