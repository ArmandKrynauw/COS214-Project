#ifndef WARSTRATEGY_H
#define WARSTRATEGY_H

class WarStrategy
{
public:
    WarStrategy();
    virtual void planOfAction() = 0;
    virtual ~WarStrategy();
};

#endif