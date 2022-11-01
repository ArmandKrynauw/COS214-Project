#include "SeaUnit.h"

SeaUnit::SeaUnit(std::string name, std::string type, int HP, int damage,
                 int value)
        : Unit(name, type, HP, damage, value) {}

SeaUnit::~SeaUnit() {}