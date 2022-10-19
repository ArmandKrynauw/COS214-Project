#include "AirUnitMedium.h"

AirUnitMedium::AirUnitMedium(std::string name, std::string type, int HP, int damage):
  AirUnit(name, type, HP, damage) {}

Entity* AirUnitMedium::clone() {
    return new AirUnitMedium(*this);
}

AirUnitMedium::~AirUnitMedium() { }