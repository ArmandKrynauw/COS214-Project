#ifndef SEAZONEFACTORY_H
#define SEAZONEFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/SeaZone.h"

class SeaZoneFactory : public ZoneFactory {
    public:
        /**
         * Provides functionality to construct a new SeaZoneFactory object
         */
        SeaZoneFactory();
        /**
         * Provides functionality to manufacture a new SeaZone
        */
        Zone *createZone(std::string ZoneName);
        /**
         * Provides functionality to destroy a SeaZoneFactory object
         */
        ~SeaZoneFactory();
};

#endif
