#ifndef LANDUNITFACTORY_H
#define LANDUNITFACTORY_H

#include "UnitFactory.h"

class LandUnitFactory : public UnitFactory {
public:
    LandUnitFactory();

    virtual Unit *createLightUnit(std::string name) override;

    virtual Unit *createMediumUnit(std::string name) override;

    virtual Unit *createHeavyUnit(std::string name) override;

    virtual ~LandUnitFactory();
};

#endif  // LANDUNITFACTORY_H