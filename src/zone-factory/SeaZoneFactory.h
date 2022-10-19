#ifndef SEAZONEFACTORY_H
#define SEAZONEFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/SeaZone.h"

class SeaZoneFactory : public ZoneFactory {
    private:
    public:
        SeaZoneFactory();
        Zone* createZone(std::string ZoneName);
        ~SeaZoneFactory();
};

#endif
