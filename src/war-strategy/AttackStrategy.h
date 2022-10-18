#ifndef ATTACKSTRATEGY_H
#define ATTACKSTRATEGY_H

#include "WarStrategy.h"

class AttackStrategy : public WarStrategy
{
public:
    AttackStrategy();
    void planOfAction();
    ~AttackStrategy();
};

#endif // ATTACKSTRATEGY_H