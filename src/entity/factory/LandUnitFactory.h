#ifndef LANDUNITFACTORY_H
#define LANDUNITFACTORY_H

#include "UnitFactory.h"

class LandUnitFactory : public UnitFactory {
public:
    LandUnitFactory();
    /**
     * Provides functionality to create a new light land unit
     * @param name Name of new light land unit
     * @return Unit pointer to new light land unit object
    */
    virtual Unit *createLightUnit(std::string name) override;
    
    /**
     * Provides functionality to create a new medium land unit
     * @param name Name of new medium land unit
     * @return Unit pointer to new medium land unit object
    */
    virtual Unit *createMediumUnit(std::string name) override;
    /**
     * Provides functionality to create a new Heavy land unit
     * @param name Name of new Heavy land unit
     * @return Unit pointer to new Heavy land unit object
    */
    virtual Unit *createHeavyUnit(std::string name) override;

    virtual ~LandUnitFactory();
};

#endif  // LANDUNITFACTORY_H