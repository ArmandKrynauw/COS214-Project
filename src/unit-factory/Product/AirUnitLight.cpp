#include "AirUnitLight.h"

AirUnitLight::AirUnitLight() : AirUnit(this->HP, this->damage) {}

AirUnitLight::~AirUnitLight()
{
    delete this;
}