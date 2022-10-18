#include "SeaUnitHeavy.h"

SeaUnitHeavy::SeaUnitHeavy() : SeaUnit(this->HP, this->damage) {}

SeaUnitHeavy::~SeaUnitHeavy()
{
    delete this;
}
