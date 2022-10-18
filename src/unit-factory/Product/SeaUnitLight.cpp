#include "SeaUnitLight.h"

SeaUnitLight::SeaUnitLight() : SeaUnit(this->HP, this->damage) {}

SeaUnitLight::~SeaUnitLight()
{
    delete this;
}
