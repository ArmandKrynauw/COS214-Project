#ifndef ENTITY_H
#define ENTITY_H

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
        ~Entity();
};
#endif