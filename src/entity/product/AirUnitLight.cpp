#include "AirUnitLight.h"

AirUnitLight::AirUnitLight(std::string name, std::string type, int HP,
                           int damage, int value)
    : AirUnit(name, type, HP, damage, value) {}

Entity* AirUnitLight::clone() {
    return new AirUnitLight(*this);
}

AirUnitLight::~AirUnitLight() {}