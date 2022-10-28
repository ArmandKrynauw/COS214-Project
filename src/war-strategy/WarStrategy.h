#ifndef WARSTRATEGY_H
#define WARSTRATEGY_H

#include <string>
class WarStrategy{
protected:
    bool planned;
    std::string target;
    std::string type;

public:
    WarStrategy(std::string target);
    void setPlanned(bool p);
    bool getPlanned();
    std::string getTarget() const;
    std::string getType();
    virtual float executeStrategy(WarStrategy* strat) = 0;
    virtual ~WarStrategy();
};

#endif