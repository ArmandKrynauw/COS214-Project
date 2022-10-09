#ifndef AIRUNITFACTORY_H
#define AIRUNITFACTORY_H


#include "UnitFactory.h"

class AirUnitFactory : public UnitFactory{
    private:
    public:
        AirUnitFactory(string name);
        Unit *createLightUnit();
        Unit *createMediumUnit();
        Unit *createHeavyUnit();
        ~AirUnitFactory();
};

#endif // AIRUNITFACTORY_H