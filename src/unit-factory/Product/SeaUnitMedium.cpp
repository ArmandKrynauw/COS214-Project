#include "SeaUnitMedium.h"

SeaUnitMedium::SeaUnitMedium() : SeaUnit(this->HP, this->damage) {}

SeaUnitMedium::~SeaUnitMedium()
{
    delete this;
}