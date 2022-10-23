#ifndef WARSTRATEGY_H
#define WARSTRATEGY_H

#include <string>
class WarStrategy{
private:
    bool planned;
    std::string defendant;

public:
    WarStrategy();
    void setPlanned(bool p);
    bool getPlanned();
    std::string getDefendant() const;
    virtual float executeStrategy(WarStrategy* strat) = 0;
    virtual ~WarStrategy();
};

#endif