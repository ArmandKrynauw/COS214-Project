#ifndef SEAUNIT_H
#define SEAUNIT_H

#include "Unit.h"

class SeaUnit : public Unit
{
private:
public:
    SeaUnit(int HP, int damage);
    void attack(Unit *unit);
    void defend(Unit *unit);
    Unit *clone();
    ~SeaUnit();
};
#endif
