#include "LandUnitMedium.h"

LandUnitMedium::LandUnitMedium(std::string name, std::string type, int HP,
                               int damage)
    : LandUnit(name, type, HP, damage) {}

Entity* LandUnitMedium::clone() {
    return new LandUnitMedium(*this);
}

LandUnitMedium::~LandUnitMedium() {}