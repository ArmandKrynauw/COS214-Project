#include "LandUnit.h"

LandUnit::LandUnit(std::string name, std::string type, int HP, int damage, int value)
        : Unit(name, type, HP, damage, value) {}

LandUnit::LandUnit(const LandUnit& LandUnit) : Unit() {};

LandUnit::~LandUnit() {}
