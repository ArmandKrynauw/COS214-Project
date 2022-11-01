#include "AirZoneFactory.h"

AirZoneFactory::AirZoneFactory() {}

Zone *AirZoneFactory::createZone(std::string ZoneName) {
    return new AirZone(ZoneName);
}

AirZoneFactory::~AirZoneFactory() {}