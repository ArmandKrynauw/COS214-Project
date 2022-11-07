#ifndef AIRTHEATREFACTORY_H
#define AIRTHEATREFACTORY_H

#include "../AirZone.h"
#include "ZoneFactory.h"
/**
 * This class is a ConcreteCreator for the ZoneFactory Factory Method Design
 * Pattern Hierarchy. This Creator creates AirZone objects to house entities of
 * type "air".
 */
class AirZoneFactory : public ZoneFactory {
   public:
    /**
     * Provides functionality to construct a new AirZoneFactory object
     */
    AirZoneFactory();
    /**
     * Provides functionality to manufacture a new AirZone
     * This function is an implementation of the FactoryMethod() of ZoneFactory.
     */
    Zone* createZone(std::string ZoneName);
    /**
     * Provides functionality to destroy a AirZoneFactory object
     */
    virtual ~AirZoneFactory();
};

#endif