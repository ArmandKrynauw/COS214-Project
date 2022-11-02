#ifndef LANDTHEATREFACTORY_H
#define LANDTHEATREFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/LandZone.h"

class LandZoneFactory : public ZoneFactory {
private:
public:
    LandZoneFactory();
    /**
     * Provides functionality to create a new land Zone
     * @param name Name of new land Zone
     * @return Zone pointer to new landZone object
    */
    Zone *createZone(std::string ZoneName);

    ~LandZoneFactory();
};

#endif