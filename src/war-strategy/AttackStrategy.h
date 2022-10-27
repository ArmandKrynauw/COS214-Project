#ifndef ATTACKSTRATEGY_H
#define ATTACKSTRATEGY_H

#include "WarStrategy.h"

class AttackStrategy : public WarStrategy
{
public:
    AttackStrategy();
    float executeStrategy(WarStrategy* strat);
    ~AttackStrategy();
};

#endif // ATTACKSTRATEGY_H