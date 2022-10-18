#include "SeaUnit.h"

SeaUnit::SeaUnit(int HP, int damage) : Unit(HP, damage) {}

Unit *SeaUnit::clone()
{
    return new SeaUnit(*this);
}
SeaUnit::~SeaUnit()
{
    delete this;
}