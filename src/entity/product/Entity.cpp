#include "Entity.h"

Entity::Entity(std::string name, std::string type){}

Entity::~Entity(){}

int Entity::getDamage() const { }

int Entity::getHP() const { }

void Entity::setName(std::string name) {
   this->name = name; 
}

