#include "LandZoneFactory.h"

LandZoneFactory::LandZoneFactory() {}

Zone *LandZoneFactory::createZone(std::string theatreName)
{
    return new LandZone(theatreName);
}

LandZoneFactory::~LandZoneFactory() {}