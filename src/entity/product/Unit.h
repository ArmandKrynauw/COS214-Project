#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity {
protected:
    int HP;
    int damage;
    int value;
    Theatre *theatre;
    int initialHP;

public:
    Unit(std::string name, std::string type, int HP, int damage, int value);

    virtual int getDamage() override;

    virtual int getHP() override;

    virtual int getValue() const override;

    std::string getName() const;

    Theatre *getTheatre();

    virtual void setTheatre(Theatre *theatre) override;

    void setHP(int HP);

    void setDamage(int damage);

    virtual bool takeDamage(int damage) override;

    virtual int getUnitCount() const override;

    void print();

    virtual Entity *clone() = 0;

    virtual nlohmann::json toJSON() const override;

    virtual nlohmann::json unitToJSON() const override;

    virtual ~Unit();
};

#endif
