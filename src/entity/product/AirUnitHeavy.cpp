#include "AirUnitHeavy.h"

AirUnitHeavy::AirUnitHeavy(std::string name, std::string type, int HP,
                           int damage)
    : AirUnit(name, type, HP, damage) {}

Entity* AirUnitHeavy::clone() {
    return new AirUnitHeavy(*this);
}

AirUnitHeavy::~AirUnitHeavy() {}