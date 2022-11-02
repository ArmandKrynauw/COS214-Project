#ifndef SEAUNITFACTORY_H
#define SEAUNITFACTORY_H

#include "UnitFactory.h"

class SeaUnitFactory : public UnitFactory {
public:
    SeaUnitFactory();
    /**
     * Provides functionality to create a new light sea unit
     * @param name Name of new light sea unit
     * @return Unit pointer to new light sea unit object
    */
    virtual Unit *createLightUnit(std::string name) override;
    /**
     * Provides functionality to create a new medium sea unit
     * @param name Name of new medium sea unit
     * @return Unit pointer to new medium sea unit object
    */
    virtual Unit *createMediumUnit(std::string name) override;
    /**
     * Provides functionality to create a new Heavy sea unit
     * @param name Name of new Heavy sea unit
     * @return Unit pointer to new Heavy sea unit object
    */
    virtual Unit *createHeavyUnit(std::string name) override;

    virtual ~SeaUnitFactory();
};

#endif  // SEAUNITFACTORY_H