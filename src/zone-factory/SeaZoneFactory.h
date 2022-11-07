#ifndef SEAZONEFACTORY_H
#define SEAZONEFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/SeaZone.h"
/**
 * This class is a ConcreteCreator for the ZoneFactory Factory Method Design Pattern Hierarchy. This Creator
 * creates SeaZone objects to house entities of type "sea".
 */
class SeaZoneFactory : public ZoneFactory {
    public:
        /**
         * Provides functionality to construct a new SeaZoneFactory object
         */
        SeaZoneFactory();
        /**
         * Provides functionality to manufacture a new SeaZone
         * This function is an implementation of the FactoryMethod() of ZoneFactory.
        */
        Zone *createZone(std::string ZoneName);
        /**
         * Provides functionality to destroy a SeaZoneFactory object
         */
        virtual ~SeaZoneFactory();
};
#endif
