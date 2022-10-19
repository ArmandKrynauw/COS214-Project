#include "LandUnitHeavy.h"

LandUnitHeavy::LandUnitHeavy(std::string name, std::string type, int HP, int damage):
  LandUnit(name, type, HP, damage) {}

Entity* LandUnitHeavy::clone() {
    return new LandUnitHeavy(*this);
}
LandUnitHeavy::~LandUnitHeavy() { }