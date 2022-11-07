#ifndef LANDUNIT_H
#define LANDUNIT_H

#include "Unit.h"

class LandUnit : public Unit {
   protected:
    LandUnit(const LandUnit& LandUnit);

   public:
    LandUnit(std::string name, std::string type, int HP, int damage, int value);

    void primitiveAttack();

    void attack(Unit* unit);

    void primitiveDefend();

    void defend(Unit* unit);

    virtual Entity* clone() override = 0;

    virtual ~LandUnit();
};

#endif
