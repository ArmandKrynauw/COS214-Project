#ifndef LANDTHEATREFACTORY_H
#define LANDTHEATREFACTORY_H

#include "ZoneFactory.h"
#include "../theatre/LandZone.h"
/**
 * This class is a ConcreteCreator for the ZoneFactory Factory Method Design Pattern Hierarchy. This Creator
 * creates LandZone objects to house entities of type "land".
 */
class LandZoneFactory : public ZoneFactory {
    public:
        /**
         * Provides functionality to construct a new LandZoneFactory object
         */
        LandZoneFactory();
        /**
         * Provides functionality to manufacture a new LandZone
         * This function is an implementation of the FactoryMethod() of ZoneFactory.
        */
        Zone *createZone(std::string ZoneName);
        /**
         * Provides functionality to destroy a LandZoneFactory object
         */
        virtual ~LandZoneFactory();
};
#endif