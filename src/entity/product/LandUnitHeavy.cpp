#include "LandUnitHeavy.h"

LandUnitHeavy::LandUnitHeavy(std::string name, std::string type, int HP,
                             int damage, int value)
        : LandUnit(name, type, HP, damage, value) {}

LandUnitHeavy::LandUnitHeavy(const LandUnitHeavy &landUnitHeavy) : LandUnit(landUnitHeavy){}

Entity *LandUnitHeavy::clone() {
    return new LandUnitHeavy(*this);
}

LandUnitHeavy::~LandUnitHeavy() {}