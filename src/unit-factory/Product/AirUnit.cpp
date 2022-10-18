#include "AirUnit.h"

AirUnit::AirUnit(int HP, int damage) : Unit(HP, damage) {}

Unit *AirUnit::clone()
{
    return new AirUnit(*this);
}

AirUnit::~AirUnit()
{
    delete this;
}