#ifndef SEAUNITFACTORY_H
#define SEAUNITFACTORY_H

#include "UnitFactory.h"

class SeaUnitFactory : public UnitFactory {
    private:
    public:
        SeaUnitFactory();
        Unit *createLightUnit(std::string name);
        Unit *createMediumUnit(std::string name);
        Unit *createHeavyUnit(std::string name);
        virtual ~SeaUnitFactory();
};

#endif // SEAUNITFACTORY_H