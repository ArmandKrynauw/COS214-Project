#include "SeaUnitMedium.h"

SeaUnitMedium::SeaUnitMedium(std::string name, std::string type, int HP, int damage):
  SeaUnit(name, type, HP, damage) {}

Entity* SeaUnitMedium::clone() {
    return new SeaUnitMedium(*this);
}

SeaUnitMedium::~SeaUnitMedium() { }