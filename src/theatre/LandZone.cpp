#include "LandZone.h"

LandZone::LandZone(std::string name) : Zone(name) {
    this->name += "_LandZone";
}

std::string LandZone::getType() {
    return "land";
}

int LandZone::getDamageDivisor() {
    return getUnitCount();
}

LandZone::~LandZone() {}