#ifndef AIRUNIT_H
#define AIRUNIT_H

#include "Unit.h"

class AirUnit : public Unit
{
private:
public:
    AirUnit(int HP, int damage);
    void primitiveAttack();
    void primitiveDefend();
    Unit *clone();
    ~AirUnit();
};

#endif // AIRUNIT_H