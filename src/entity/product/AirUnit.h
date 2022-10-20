#ifndef AIRUNIT_H
#define AIRUNIT_H

#include "Unit.h"

class AirUnit : public Unit {
   public:
    AirUnit(std::string name, std::string type, int HP, int damage);
    void primitiveAttack();
    void attack(Unit* unit);
    void primitiveDefend();
    void defend(Unit* unit);
    virtual Entity* clone() override = 0;
    virtual ~AirUnit();
};

#endif  // AIRUNIT_H