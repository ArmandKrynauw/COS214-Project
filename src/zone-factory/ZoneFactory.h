#ifndef ZONEFACTORY_H
#define ZONEFACTORY_H

#include <iostream> //remove later (Testing purposes)

#include "../theatre/Zone.h"

class ZoneFactory
{ 
    private: 
    Zone * zone;
    public: 
    ZoneFactory();
    virtual Zone *createZone(std::string ZoneName) = 0;
    ~ZoneFactory();
};




#endif
