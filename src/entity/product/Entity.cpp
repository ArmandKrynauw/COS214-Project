#include "Entity.h"

Entity::Entity(std::string name, std::string type) {
    this->name = name;
    this->type = type;
}

Entity::~Entity() {}

int Entity::getDamage() const {}

std::string Entity::getId() const {
    return id;
}

std::string Entity::getName() const {
    return name;
}

void Entity::setName(std::string name) {
    this->name = name;
}

std::string Entity::getType() const {
    return type;
}
