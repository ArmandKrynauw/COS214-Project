#include "SeaUnitHeavy.h"

SeaUnitHeavy::SeaUnitHeavy(std::string name, std::string type, int HP, int damage):
  SeaUnit(name, type, HP, damage) {}

Entity* SeaUnitHeavy::clone() {
    return new SeaUnitHeavy(*this);
}

SeaUnitHeavy::~SeaUnitHeavy() { }
