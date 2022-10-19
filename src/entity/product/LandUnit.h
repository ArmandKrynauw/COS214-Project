#ifndef LANDUNIT_H
#define LANDUNIT_H

#include "Unit.h"

class LandUnit : public Unit{
    private:
    public:
        LandUnit(std::string name, std::string type, int HP, int damage);
        void primitiveAttack();
        void attack(Unit *unit);
        void primitiveDefend();
        void defend(Unit *unit);
        virtual Entity* clone() override = 0;
        ~LandUnit();
};
#endif
