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

int ArmedForce::getDamage() const {
    int damage = 0;
    std::vector<Entity*>::const_iterator it;

    for (it = entities.begin(); it != entities.end(); ++it) {
        damage += (*it)->getDamage();
    }

    return damage;
}

int ArmedForce::getHP() const {
    int HP = 0;
    std::vector<Entity*>::const_iterator it;

    for (it = entities.begin(); it != entities.end(); ++it) {
        HP += (*it)->getHP();
    }

    return HP;
     
}

bool ArmedForce::takeDamage(int damage) {
    // TODO: Needs discussing on what happens if Entities die
    int index = rand() % entities.size();
    entities[index]->takeDamage(damage);
    return entities[index]->getHP();
}

int ArmedForce::getUnitCount() const {
    int capacity = 0;
    std::vector<Entity*>::const_iterator it;

    for (it = entities.begin(); it != entities.end(); ++it) {
        capacity += (*it)->getUnitCount();
    }

    return capacity;
}

int ArmedForce::getValue() const {
    int value = 0;

    for (Entity* entity : entities) {
        value += entity->getValue();
    }

    return value;
}

void ArmedForce::setTheatre(Theatre* theatre) {
    std::vector<Entity*>::iterator it;
    for (it = entities.begin(); it != entities.end(); ++it) {
        (*it)->setTheatre(theatre);
    }
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
