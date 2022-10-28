#include "Faction.h"



Faction::Faction(std::string name) {
    this->name = name;
    this->id = uuid::generate();
    baseResourceCount = 0;
}

std::string Faction::getName() {
    return name;
}

std::string Faction::getId() const {
    return id;
}

bool Faction::equals(Faction* faction) const {
    return id == faction->id;
}

void Faction::setName(std::string name) {
    this->name = name;
}

