#include "SeaZoneFactory.h"

SeaZoneFactory::SeaZoneFactory() {}

Zone *SeaZoneFactory::createZone(std::string theatreName)
{
    return new SeaZone(theatreName);
}

SeaZoneFactory::~SeaZoneFactory() {}