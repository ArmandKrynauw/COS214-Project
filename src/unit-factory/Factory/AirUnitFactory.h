#ifndef AIRUNITFACTORY_H
#define AIRUNITFACTORY_H


#include "UnitFactory.h"

class AirUnitFactory : public UnitFactory{
    private:
    public:
        AirUnitFactory();
        Unit *createLightUnit(std::string name);
        Unit *createMediumUnit(std::string name);
        Unit *createHeavyUnit(std::string name);
        virtual ~AirUnitFactory();
};

#endif // AIRUNITFACTORY_H