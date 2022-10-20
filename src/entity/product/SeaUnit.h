#ifndef SEAUNIT_H
#define SEAUNIT_H

#include "Unit.h"

class SeaUnit : public Unit {
   private:
   public:
    SeaUnit(std::string name, std::string type, int HP, int damage);
    void primitiveAttack();
    void attack(Unit* unit);
    void primitiveDefend();
    void defend(Unit* unit);
    virtual Entity* clone() = 0;
    ~SeaUnit();
};
#endif
