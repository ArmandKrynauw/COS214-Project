#ifndef ZONEFACTORY_H
#define ZONEFACTORY_H

#include <iostream> //remove later (Testing purposes)

#include "../theatre/Zone.h"

class ZoneFactory {
private:
    Zone *zone;
public:
    ZoneFactory();
        /**
     * Provides functionality to create a new Zone
     * @param name Name of new  Zone
     * @return Zone pointer to new object
    */
    virtual Zone *createZone(std::string ZoneName) = 0;

    ~ZoneFactory();
};


#endif
