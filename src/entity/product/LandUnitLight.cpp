#include "LandUnitLight.h"

LandUnitLight::LandUnitLight(std::string name, std::string type, int HP,
                             int damage, int value)
    : LandUnit(name, type, HP, damage, value) {}

Entity* LandUnitLight::clone() {
    return new LandUnitLight(*this);
}

LandUnitLight::~LandUnitLight() {}