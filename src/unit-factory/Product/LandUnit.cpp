#include "LandUnit.h"

LandUnit::LandUnit(int HP, int damage) : Unit(HP, damage) {}

Unit *LandUnit::clone()
{
    return new LandUnit(*this);
}

LandUnit::~LandUnit()
{
    delete this;
}
