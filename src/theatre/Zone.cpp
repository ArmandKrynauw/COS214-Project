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

int Zone::sum()
{
    int sum = 0;
    for(int i=0;i<units.size();i++)
    {
        sum+=units.at(i)->getDamage();
    }
    return sum;
}