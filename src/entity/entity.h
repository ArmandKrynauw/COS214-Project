#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

class Entity {
    private:
        int hp;
        int damage;

    public:
        Entity();
        int getHP();
        void setHP(int a);
        virtual int getDamage();
        void setDamage(int a);
        virtual std::string print();
        ~Entity();
};
#endif // ENTITY_H