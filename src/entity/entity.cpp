#include "entity.h"


Entity::Entity(){}

Entity::~Entity(){}

int Entity::getDamage(){ 
    return damage;
}

void Entity::setDamage(int damage) { 
    damage = damage;
}

int Entity::getHP(){
    return hp;
}

void Entity::setHP(int hp){
    this->hp = hp;
}
