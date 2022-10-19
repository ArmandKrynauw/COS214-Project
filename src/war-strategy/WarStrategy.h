#ifndef WARSTRATEGY_H
#define WARSTRATEGY_H

class WarStrategy{
private:
    bool planned;

public:
    WarStrategy();
    void setPlanned(bool p);
    bool getPlanned();
    virtual float executeStrategy(WarStrategy* strat) = 0;
    virtual ~WarStrategy();
};

#endif