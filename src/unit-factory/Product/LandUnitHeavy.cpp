#include "LandUnitHeavy.h"

LandUnitHeavy::LandUnitHeavy() : LandUnit(this->HP, this->damage) {}

LandUnitHeavy::~LandUnitHeavy()
{
    delete this;
}