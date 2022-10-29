#include "Zone.h"
#include "../entity/product/Entity.h"

Zone::Zone(std::string name)
{
    this->name = name;
    this->id = uuid::generate();
}

void Zone::addEntity(Entity* entity) {
    entities.push_back(entity);
}

Entity* Zone::removeEntity(int index)
{
    Entity* temp = entities.at(index);
    entities.erase(entities.begin()+index-1);
    return temp;
}

int Zone::getTotalDamage() {
    int sum = 0;
    for(int i=0;i<entities.size();i++){
        sum += entities[i]->getDamage();
    }
    return sum;
}

void Zone::takeDamage(int damage) {
    int divisor = getDamageDivisor();
    int hit = damage / divisor;

    for (int i = 0; i < divisor; i++){
        int random = (rand() % entities.size());
        if(entities[random]->takeDamage(hit)){
            entities.erase(entities.begin() + random);
        }
    }
}

int Zone::getUnitCount() const {
    int capacity = 0;

    for (int i = 0; i < entities.size(); i++) {
        capacity += entities[i]->getUnitCount();
    }

    return capacity ;
}

std::vector<Entity*> Zone::getEntities(){
    return entities;
}

std::string Zone::getName() const {
    return name;
}

Zone::~Zone() {}
