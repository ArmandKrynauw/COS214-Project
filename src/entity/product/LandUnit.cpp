#include "LandUnit.h"

LandUnit::LandUnit(std::string name, std::string type, int HP, int damage)
    : Unit(name, type, HP, damage) {}

LandUnit::~LandUnit() {}
