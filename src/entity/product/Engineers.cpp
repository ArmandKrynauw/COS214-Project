#include "Engineers.h"

Engineers::Engineers(Entity* entity) : SupportCompany(entity) {
    //entity->setName(entity->getName() + "-EG");
}

int Engineers::getDamage() {
    return SupportCompany::getDamage() * 1.25;
}

int Engineers::getHP() {
    return SupportCompany::getHP();
}

std::string Engineers::getName(){
    return entity->getName() + "-EG";
}

Engineers::~Engineers() {

}