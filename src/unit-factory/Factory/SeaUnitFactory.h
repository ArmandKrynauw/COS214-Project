#ifndef SEAUNITFACTORY_H
#define SEAUNITFACTORY_H



#include "UnitFactory.h"

class SeaUnitFactory : public UnitFactory{
    private:
    public:
        SeaUnitFactory();
        Unit *createLightUnit();
        Unit *createMediumUnit();
        Unit *createHeavyUnit();
        ~SeaUnitFactory();
};

#endif // SEAUNITFACTORY_H