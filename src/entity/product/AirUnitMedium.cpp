#include "AirUnitMedium.h"

AirUnitMedium::AirUnitMedium(std::string name, std::string type, int HP, int damage, int value)
        : AirUnit(name, type, HP, damage, value) {}

AirUnitMedium::AirUnitMedium(const AirUnitMedium &airUnitMedium) : AirUnit(airUnitMedium) {}

Entity *AirUnitMedium::clone() {
    return new AirUnitMedium(*this);
}

AirUnitMedium::~AirUnitMedium() {}