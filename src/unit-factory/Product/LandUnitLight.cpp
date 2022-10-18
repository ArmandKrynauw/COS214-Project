#include "LandUnitLight.h"

LandUnitLight::LandUnitLight() : LandUnit(this->HP, this->damage)
{
}

LandUnitLight::~LandUnitLight()
{
    delete this;
}