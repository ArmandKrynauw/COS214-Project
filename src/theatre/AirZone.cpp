#include "AirZone.h"

AirZone::AirZone(std::string name) : Zone(name) {
    this->name += "_AirZone";
}

std::string AirZone::getType() {
    return "air";
}

int AirZone::getDamageDivisor() {
    return getUnitCount() * 2;
}

AirZone::~AirZone() {}