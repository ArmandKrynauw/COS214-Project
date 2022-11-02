#ifndef SEAZONEFACTORY_H
#define SEAZONEFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/SeaZone.h"

class SeaZoneFactory : public ZoneFactory {
private:
public:
    SeaZoneFactory();
    /**
     * Provides functionality to create a new sea Zone
     * @param name Name of new sea Zone
     * @return Zone pointer to new seaZone object
    */
    Zone *createZone(std::string ZoneName);

    ~SeaZoneFactory();
};

#endif
