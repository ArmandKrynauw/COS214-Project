#include "LandZoneFactory.h"

LandZoneFactory::LandZoneFactory() {}

Zone *LandZoneFactory::createZone(std::string ZoneName) {
    return new LandZone(ZoneName);
}

LandZoneFactory::~LandZoneFactory() {}