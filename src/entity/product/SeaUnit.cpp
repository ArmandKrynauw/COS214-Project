#include "SeaUnit.h"

SeaUnit::SeaUnit(std::string name, std::string type, int HP, int damage)
    : Unit(name, type, HP, damage) {}

SeaUnit::~SeaUnit() {}