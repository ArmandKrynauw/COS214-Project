#ifndef AIRTHEATREFACTORY_H
#define AIRTHEATREFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/AirZone.h"

class AirZoneFactory : public ZoneFactory {
    public:
        /**
         * Provides functionality to construct a new AirZoneFactory object
         */
        AirZoneFactory();
        /**
         * Provides functionality to manufacture a new AirZone
        */
        Zone *createZone(std::string ZoneName);
        /**
        * Provides functionality to destroy a AirZoneFactory object
        */
        ~AirZoneFactory();
};

#endif