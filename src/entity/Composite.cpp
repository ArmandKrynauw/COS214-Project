#include "Composite.h"

Composite::Composite(){}

Composite::~Composite(){}

int Composite::getDamage(){
    return Entity::getDamage();
}

void Composite::update(){
    int damage = 0;
    for (int i = 0; i < units.size(); i++)
    {
        damage+= units.at(i)->getDamage();
    }
    this->setDamage(damage);
}