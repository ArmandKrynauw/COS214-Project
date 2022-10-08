#pragma once

class Entity 
{
    private:
    int hp;
    int damage;

    public:
    Entity();
    ~Entity();
    int getHP();
    void setHP(int a);
    virtual int getDamage();
    void setDamage(int a);
};