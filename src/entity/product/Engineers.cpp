#include "Engineers.h"

Engineers::Engineers(Entity* entity) : SupportCompany(entity) { }

int Engineers::getDamage() const {
    return SupportCompany::getDamage() * 1.25;
}

std::string Engineers::getName() const {
    return entity->getName() + "-EG";
}

Engineers::~Engineers() { }