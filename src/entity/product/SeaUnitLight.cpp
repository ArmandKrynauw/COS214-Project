#include "SeaUnitLight.h"

SeaUnitLight::SeaUnitLight(std::string name, std::string type, int HP, int damage, int value)
        : SeaUnit(name, type, HP, damage, value) {}

SeaUnitLight::SeaUnitLight(const SeaUnitLight& seaUnitLight) : SeaUnit(seaUnitLight) { }

Entity *SeaUnitLight::clone() {
    return new SeaUnitLight(*this);
}

SeaUnitLight::~SeaUnitLight() {}
