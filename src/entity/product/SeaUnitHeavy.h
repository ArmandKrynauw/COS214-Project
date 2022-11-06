#ifndef SEAUNITHEAVY_H
#define SEAUNITHEAVY_H

#include "SeaUnit.h"

class SeaUnitHeavy : public SeaUnit {
protected:
    SeaUnitHeavy(const SeaUnitHeavy &seaUnitHeavy);
public:
    SeaUnitHeavy(std::string name, std::string type, int HP, int damage,
                 int value);

    virtual Entity *clone() override;

    ~SeaUnitHeavy();
};

#endif
