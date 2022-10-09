#ifndef LANDUNITFACTORY_H
#define LANDUNITFACTORY_H

#include "UnitFactory.h"

class LandUnitFactory : public UnitFactory {
    private:
    public:
        LandUnitFactory();
        Unit *createLightUnit(std::string name);
        Unit *createMediumUnit(std::string name);
        Unit *createHeavyUnit(std::string name);
        virtual ~LandUnitFactory();
};

#endif // LANDUNITFACTORY_H