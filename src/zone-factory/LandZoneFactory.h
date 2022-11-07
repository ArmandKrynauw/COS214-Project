#ifndef LANDTHEATREFACTORY_H
#define LANDTHEATREFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/LandZone.h"

class LandZoneFactory : public ZoneFactory {
    public:
        /**
         * Provides functionality to construct a new LandZoneFactory object
         */
        LandZoneFactory();
        /**
         * Provides functionality to manufacture a new LandZone
        */
        Zone *createZone(std::string ZoneName);
        /**
         * Provides functionality to destroy a LandZoneFactory object
         */
        ~LandZoneFactory();
};

#endif