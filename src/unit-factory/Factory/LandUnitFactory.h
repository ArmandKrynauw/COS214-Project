#ifndef LANDUNITFACTORY_H
#define LANDUNITFACTORY_H

#include "UnitFactory.h"

class LandUnitFactory : public UnitFactory{
    private:
    public:
        LandUnitFactory();
        Unit *createLightUnit();
        Unit *createMediumUnit();
        Unit *createHeavyUnit();
        ~LandUnitFactory();
};

#endif // LANDUNITFACTORY_H