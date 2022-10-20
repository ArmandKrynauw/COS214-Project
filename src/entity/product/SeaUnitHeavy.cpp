#include "SeaUnitHeavy.h"

SeaUnitHeavy::SeaUnitHeavy(std::string name, std::string type, int HP,
                           int damage, int value)
    : SeaUnit(name, type, HP, damage, value) {}

Entity* SeaUnitHeavy::clone() {
    return new SeaUnitHeavy(*this);
}

SeaUnitHeavy::~SeaUnitHeavy() {}
