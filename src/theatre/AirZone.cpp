#include "AirZone.h"

AirZone::AirZone(std::string name) : Zone(name) {
    this->name+="_AirZone";
}

std::string AirZone::getType(){
    return "air";
}

int AirZone::getDamageDivisor() {
    // Planes have much higher contact rates with the enemy, however lower losses per engagement generally.
    return getUnitCount() * 2;
}

AirZone::~AirZone() {}