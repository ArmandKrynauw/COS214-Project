#include "Theatre.h"

Theatre::Theatre(std::string name, bool seaZone)
{
    this->name = name;
    this->id = uuid::generate();
    if(seaZone) this->limit = 3;
    else
    this->limit = 2;
}

Theatre::~Theatre()
{
    
}

void Theatre::addFaction(std::string name)
{
    factions.insert(name,factions.size());

    std::vector<Zone*> army;

    army.push_back(landFactory->createZone());
    army.push_back(airFactory->createZone());
    if(limit==3) army.push_back(seaFactory->createZone());

    armies.insert(army);
}

void Theatre::removeFaction(std::string name)
{
    auto it = factions.find(name);
    int index = it->second;

    army.at(index).at(0)->~Zone();
    army.at(index).at(1)->~Zone();
    if(limit==3) army.at(index).at(2)->~Zone();

    army.erase(index);
}

std::string Theatre::getName() const {
    return name;
}

void addUnit(std::string faction,Unit* unit)
{
    auto it = factions.find(name);
    int index = it->second;

    if(unit)
    army.at(index)
}

Unit* removeUnit(std::string faction,int type,int index)
{
    auto it = factions.find(name);
    int index = it->second;


    Unit* unit =  armies.at(index).at(type)->removeUnit(index);

    return unit;

}

