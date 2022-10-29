#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity {
   protected:
    int HP;
    int damage;
    int value;

   public:
    Unit(std::string name, std::string type, int HP, int damage, int value);
    virtual int getHP() const;
    virtual int getDamage() const override;
    virtual int getValue() const override;
    std::string getName() const;
    void setHP(int HP);
    void setDamage(int damage);
    virtual bool takeDamage(int damage);
    void print();
    virtual Entity* clone() = 0;
    virtual ~Unit();
};

#endif