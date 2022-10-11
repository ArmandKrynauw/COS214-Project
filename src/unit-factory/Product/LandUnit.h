#ifndef LANDUNIT_H
#define LANDUNIT_H

#include "Unit.h"

class LandUnit : public Unit
{
private:
public:
    LandUnit(int HP, int damage);
    void primitiveAttack();
    void primitiveDefend();
    Unit *clone();
    ~LandUnit();
};
#endif
