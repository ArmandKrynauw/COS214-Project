#include "SeaUnitMedium.h"

SeaUnitMedium::SeaUnitMedium(std::string name, std::string type, int HP,
                             int damage, int value)
    : SeaUnit(name, type, HP, damage, value) {}

Entity* SeaUnitMedium::clone() {
    return new SeaUnitMedium(*this);
}

SeaUnitMedium::~SeaUnitMedium() {}