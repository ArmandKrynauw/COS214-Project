#include "LandUnitMedium.h"

LandUnitMedium::LandUnitMedium(std::string name, std::string type, int HP,
                               int damage, int value)
    : LandUnit(name, type, HP, damage, value) {}

Entity* LandUnitMedium::clone() {
    return new LandUnitMedium(*this);
}

LandUnitMedium::~LandUnitMedium() {}