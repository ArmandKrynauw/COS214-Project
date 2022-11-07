#ifndef ZONEFACTORY_H
#define ZONEFACTORY_H

#include <iostream>

#include "../theatre/Zone.h"
/**
 * This is class is the AbstractCreator for the Factory Method Design Pattern. This pattern is
 * used to create different zones to be housed in theatres which is used for the 3 different types
 * of entities to fight being "land", "sea" or "air".
 */
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
         * This function is the Abstract FactoryMethod()
        */
        virtual Zone *createZone(std::string ZoneName) = 0;
        /**
        * Provides functionality to destroy a ZoneFactory object
        */
        virtual ~ZoneFactory();
};
#endif
