#include "SeaUnitMedium.h"

SeaUnitMedium::SeaUnitMedium(std::string name, std::string type, int HP, int damage, int value)
        : SeaUnit(name, type, HP, damage, value) {}


SeaUnitMedium::SeaUnitMedium(const SeaUnitMedium & seaUnitMedium) : SeaUnit(seaUnitMedium){}

Entity *SeaUnitMedium::clone() {
    return new SeaUnitMedium(*this);
}

SeaUnitMedium::~SeaUnitMedium() {}