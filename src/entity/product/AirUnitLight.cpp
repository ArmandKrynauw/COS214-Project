#include "AirUnitLight.h"

AirUnitLight::AirUnitLight(std::string name, std::string type, int HP,
                           int damage)
    : AirUnit(name, type, HP, damage) {}

Entity* AirUnitLight::clone() {
    return new AirUnitLight(*this);
}

AirUnitLight::~AirUnitLight() {}