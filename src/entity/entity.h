#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>


class Entity {
    private:
        int hp;
        int damage;
        std::string name;

    public:
        Entity();
        int getHP();
        void setHP(int a);
        virtual int getDamage();
        void setDamage(int a);
        std::string getName();
        void setName(std::string name);
        virtual std::string print() = 0;
        ~Entity();
};
#endif // ENTITY_H