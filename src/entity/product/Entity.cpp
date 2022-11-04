#include "Entity.h"

Entity::Entity() {}

Entity::Entity(std::string name, std::string type) {
    this->name = name;
    this->type = type;
    this->id = uuid::generate();
}

Entity::~Entity() {}

std::string Entity::getId() const {
    return id;
}

std::string Entity::getName() {
    return name;
}

void Entity::setName(std::string name) {
    this->name = name;
}

std::string Entity::getType() const {
    return type;
}

void Entity::clearCasualties() {}

void Entity::setDamage(int damage) {
    
}

Theatre* Entity::getTheatre(){

}

 void Entity::setHP(int hp){

 }






