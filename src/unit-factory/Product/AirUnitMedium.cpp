#include "AirUnitMedium.h"

AirUnitMedium::AirUnitMedium() : AirUnit(this->HP, this->damage) {}

AirUnitMedium::~AirUnitMedium()
{
    delete this;
}