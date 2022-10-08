#include "Faction.h"

Faction::Faction(std::string name) { this->name = name; }

std::string Faction::getName() { return name; }

void Faction::setName(std::string name) { this->name = name; }