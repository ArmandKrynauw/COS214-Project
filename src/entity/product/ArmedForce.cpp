#include "ArmedForce.h"

ArmedForce::ArmedForce(std::string name, std::string type) : Entity(name, type) {}

ArmedForce::~ArmedForce() {}

void ArmedForce::add(Entity* entity) {
    entities.push_back(entity);
}

void ArmedForce::remove(Entity* entity) {
    std::vector<Entity* >::iterator it;
    for (it = entities.begin(); it != entities.end(); ++it) {
        if ((*it)->getId() == entity->getId()) {
            entities.erase(it);
        }
    }
}

int ArmedForce::getDamage() const {}

int ArmedForce::getValue() const {
    int value = 0;

    for (Entity* entity : entities) {
        value += entity->getValue();
    }

    return value;
}

Entity* ArmedForce::clone() {}

void ArmedForce::update() {
    int damage = 0;
    for(int i = 0; i < entities.size(); i++) {
        damage += entities.at(i)->getDamage();
    }
    // this->setDamage(damage);
}

void ArmedForce::print(){
    std::vector<Entity*>::iterator it;

    for(it = entities.begin(); it != entities.end(); it++){
        (*it)->print();
    }
}
