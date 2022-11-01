#include "SeaZoneFactory.h"

SeaZoneFactory::SeaZoneFactory() {}

Zone *SeaZoneFactory::createZone(std::string ZoneName) {
    return new SeaZone(ZoneName);
}

SeaZoneFactory::~SeaZoneFactory() {}