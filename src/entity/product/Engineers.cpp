#include "Engineers.h"

Engineers::Engineers(Entity* entity) : SupportCompany(entity) {}

Engineers::Engineers(const Engineers& engineers) : SupportCompany(engineers) {}

int Engineers::getDamage() const {
    return SupportCompany::getDamage() * 1.25;
}

std::string Engineers::getName() const {
    return entity->getName() + "-EG";
}

Entity* Engineers::clone() {
   return new Engineers(*this);
}

Engineers::~Engineers() { }