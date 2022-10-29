#ifndef AIRTHEATREFACTORY_H
#define AIRTHEATREFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/AirZone.h"

class AirZoneFactory : public ZoneFactory {
    private:
    public:
        AirZoneFactory();
        Zone* createZone(std::string ZoneName);
        ~AirZoneFactory();
};

#endif