#include "Zone.h"

Zone::Zone(std::string name)
{
    this->name = name;
    this->id = uuid::generate();
}

void Zone::addUnit(Unit* unit)
{
    units.push_back(unit);
}

Unit* Zone::removeUnit(int index)
{
    Unit* temp = units.at(index);
    units.erase(units.begin()+index-1);
    return temp;
}

std::string Zone::getType() const {
    return type; 
}

int Zone::sum()
{
    int sum = 0;
    for(int i=0;i<units.size();i++)
    {
        sum+=units.at(i)->getDamage();
    }
    return sum;
}

std::vector<Unit*> Zone::getUnits(){
    return units;
}

std::string Zone::getName() const {
    return name;
}

Zone::~Zone() {}