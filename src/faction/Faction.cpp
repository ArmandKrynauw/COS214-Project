#include "Faction.h"

Faction::Faction(std::string name) {
    this->name = name;
    this->id = uuid::generate();

    int nums[3] = {0,0,0};
    for(int i : nums){
        research.push_back(i);
    }
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
    if(category == "industry"){
        research[0] += researchPoints;
    }
    else if(category == "propaganda"){
        research[1] += researchPoints;
    }

 }

void Faction::setBaseResourceCount(int baseResource)
{
    this->baseResourceCount = baseResource;
}

int Faction::getBaseResourceCount(){
    return baseResourceCount;
}

Faction::~Faction(){}

int Faction::getMorale(){
    return this->morale;
}

void Faction::setMorale(int morale)
{
    this->morale = morale;
}


