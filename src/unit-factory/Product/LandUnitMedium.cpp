#include "LandUnitMedium.h"

LandUnitMedium::LandUnitMedium() : LandUnit(this->HP, this->damage) {}

LandUnitMedium::~LandUnitMedium()
{
    delete this;
}