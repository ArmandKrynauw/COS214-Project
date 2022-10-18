#ifndef UNIT_H
#define UNIT_H

#include <iostream>
using namespace std;

class Unit
{
private:
    int HP;
    int damage;

public:
    Unit(int HP, int damage);
    int getHP();
    int getDamage();
    void setHP(int HP);
    void setDamge(int damage);
    std::string print();
    virtual Unit *clone() = 0;
    virtual ~Unit();
};
#endif
