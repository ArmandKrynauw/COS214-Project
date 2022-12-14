#ifndef AIRUNIT_H
#define AIRUNIT_H

#include "Unit.h"

class AirUnit : public Unit {
   protected:
    AirUnit(const AirUnit& airUnit);

   public:
    AirUnit(std::string name, std::string type, int HP, int damage, int value);

    void primitiveAttack();

    void attack(Unit* unit);

    void primitiveDefend();

    void defend(Unit* unit);

    virtual Entity* clone() override = 0;

    virtual ~AirUnit();
};

#endif  // AIRUNIT_H