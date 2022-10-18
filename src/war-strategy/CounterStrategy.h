#ifndef COUNTERSTRATEGY_H
#define COUNTERSTRATEGY_H

#include "WarStrategy.h"

class CounterStrategy : public WarStrategy
{
public:
    CounterStrategy();
    void planOfAction();
    ~CounterStrategy();
};

#endif // COUNTERSTRATEGY_H