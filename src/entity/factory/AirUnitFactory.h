#ifndef AIRUNITFACTORY_H
#define AIRUNITFACTORY_H

#include "UnitFactory.h"

class AirUnitFactory : public UnitFactory {
    public:
        AirUnitFactory();
        virtual Unit* createLightUnit(std::string name) override;
        virtual Unit* createMediumUnit(std::string name) override;
        virtual Unit* createHeavyUnit(std::string name) override;
        virtual ~AirUnitFactory();
};

#endif // AIRUNITFACTORY_H