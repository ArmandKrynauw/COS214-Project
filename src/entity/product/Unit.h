#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity {
   protected:
    int HP;
    int damage;
    int value;
    Theatre* theatre;

   public:
    Unit(std::string name, std::string type, int HP, int damage, int value);
    virtual int getDamage() const override;
    virtual int getHP() const override;
    virtual int getValue() const override;
    std::string getName() const;
    std::string getTheatre() const;
    void setHP(int HP);
    void setDamage(int damage);
    virtual bool takeDamage(int damage) override;
    virtual int getUnitCount() const override;
    void print();
    virtual void setTheatre(Theatre* theatre) override;
    virtual Entity* clone() = 0;
    virtual ~Unit();
};

#endif
