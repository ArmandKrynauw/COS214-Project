#include "LandZone.h"

LandZone::LandZone(std::string name) : Zone(name) {
    this->name += "_LandZone";
}

std::string LandZone::getType() {
    return "land";
}

int LandZone::getDamageDivisor() {
    // Ground forces tend to have unpredictable engagements just as often as expected engagements.
    return getUnitCount();
}

LandZone::~LandZone() {}