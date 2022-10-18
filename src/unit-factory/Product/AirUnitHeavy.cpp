#include "AirUnitHeavy.h"

AirUnitHeavy::AirUnitHeavy() : AirUnit(this->HP, this->damage) {}

AirUnitHeavy::~AirUnitHeavy()
{
    delete this;
}