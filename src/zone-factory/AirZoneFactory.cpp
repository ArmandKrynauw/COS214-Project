#include "AirZoneFactory.h"

AirZoneFactory::AirZoneFactory() {}

Zone *AirZoneFactory::createZone(std::string theatreName)
{
    return new AirZone(theatreName);
}

AirZoneFactory::~AirZoneFactory() {}