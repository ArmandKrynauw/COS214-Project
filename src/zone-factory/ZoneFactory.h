#ifndef ZONEFACTORY_H
#define ZONEFACTORY_H

#include <iostream> //remove later (Testing purposes)

#include "../theatre/Zone.h"

class ZoneFactory {
    private:
        Zone *zone;
    public:
        /**
         * Provides functionality to construct a new ZoneFactory object
         * 
         */
        ZoneFactory();
        /**
         * Pure virtual function to be implemented in child classes.
        */
        virtual Zone *createZone(std::string ZoneName) = 0;
        /**
        * Provides functionality to destroy a ZoneFactory object
        */
        ~ZoneFactory();
};


#endif
