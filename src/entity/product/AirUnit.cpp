#include "AirUnit.h"

AirUnit::AirUnit(std::string name, std::string type, int HP, int damage, int value)
        : Unit(name, type, HP, damage, value) {}

AirUnit::AirUnit(const AirUnit& airUnit) : Unit() {};

AirUnit::~AirUnit() {}