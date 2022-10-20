#ifndef UNIT_H
#define UNIT_H

#include "../state/UnitState.h"
#include "Entity.h"

class Unit : public Entity {
   protected:
    int HP;
    int damage;
    int value;
    UnitState* state;

   public:
    Unit(std::string name, std::string type, int HP, int damage, int value);
    virtual int getHP() const override;
    virtual int getDamage() const override;
    void setHP(int HP);
    void setDamage(int damage);
    virtual void takeDamage(int damage);
    std::string print();
    virtual Entity* clone() = 0;
    virtual ~Unit();
};

#endif
