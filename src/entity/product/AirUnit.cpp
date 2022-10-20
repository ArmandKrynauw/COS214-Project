#include "AirUnit.h"

AirUnit::AirUnit(std::string name, std::string type, int HP, int damage)
    : Unit(name, type, HP, damage) {}

AirUnit::~AirUnit() {}