#include "Faction.h"

Faction::Faction(std::string name) {
    this->name = name;
    this->id = uuid::generate();
}

std::string Faction::getName() {
    return name;
}

std::string Faction::getId() const {
    return id;
}

bool Faction::equals(Faction *faction) const {
    return id == faction->id;
}

void Faction::setName(std::string name) {
    this->name = name;
}

 void Faction::setResearch(int researchPoints,std::string category)
 {
    if(category=="industry") research.at(0) += researchPoints;
    else
    if(category=="propaganda") research.at(1) += researchPoints;

 }

    Faction::~Faction(){}
