#include "LandUnitLight.h"

LandUnitLight::LandUnitLight(std::string name, std::string type, int HP, int damage):
  LandUnit(name, type, HP, damage) {}

Entity* LandUnitLight::clone() {
    return new LandUnitLight(*this);
}

LandUnitLight::~LandUnitLight() { }