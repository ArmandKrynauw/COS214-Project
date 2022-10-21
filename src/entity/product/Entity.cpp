#include "Entity.h"

Entity::Entity(std::string name, std::string type) {}

Entity::~Entity() {}

int Entity::getDamage() const {}

std::string Entity::getId() const {
    return id;
}

void Entity::setName(std::string name) {
    this->name = name;
}
