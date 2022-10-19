#include "SeaUnitLight.h"

SeaUnitLight::SeaUnitLight(std::string name, std::string type, int HP, int damage):
  SeaUnit(name, type, HP, damage) {}

Entity* SeaUnitLight::clone() {
    return new SeaUnitLight(*this);
}

SeaUnitLight::~SeaUnitLight() { }
