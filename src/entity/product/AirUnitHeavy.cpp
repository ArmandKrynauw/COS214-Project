#include "AirUnitHeavy.h"

AirUnitHeavy::AirUnitHeavy(std::string name, std::string type, int HP,
                           int damage, int value)
    : AirUnit(name, type, HP, damage, value) {}

Entity* AirUnitHeavy::clone() {
    return new AirUnitHeavy(*this);
}

AirUnitHeavy::~AirUnitHeavy() {}