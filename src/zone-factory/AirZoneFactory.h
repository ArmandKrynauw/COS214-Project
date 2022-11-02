#ifndef AIRTHEATREFACTORY_H
#define AIRTHEATREFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/AirZone.h"

class AirZoneFactory : public ZoneFactory {
private:
public:
    AirZoneFactory();
    /**
     * Provides functionality to create a new air Zone
     * @param name Name of new air Zone
     * @return Zone pointer to new AirZone object
    */

    Zone *createZone(std::string ZoneName);

    ~AirZoneFactory();
};

#endif