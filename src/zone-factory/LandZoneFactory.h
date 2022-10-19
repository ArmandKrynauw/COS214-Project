#ifndef LANDTHEATREFACTORY_H
#define LANDTHEATREFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/LandZone.h"

class LandZoneFactory : public ZoneFactory
{
private:
public:
    LandZoneFactory();
    Zone *createZone(std::string theatreName);
    ~LandZoneFactory();
};

#endif