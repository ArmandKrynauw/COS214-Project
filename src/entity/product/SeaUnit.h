#ifndef SEAUNIT_H
#define SEAUNIT_H

#include "Unit.h"

class SeaUnit : public Unit {
protected:
    SeaUnit(const SeaUnit& seaUnit);

public:
    SeaUnit(std::string name, std::string type, int HP, int damage, int value);

    void primitiveAttack();

    void attack(Unit *unit);

    void primitiveDefend();

    void defend(Unit *unit);

    virtual Entity *clone() = 0;

    virtual ~SeaUnit();
};

#endif
