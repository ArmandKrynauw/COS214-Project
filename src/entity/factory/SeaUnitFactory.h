#ifndef SEAUNITFACTORY_H
#define SEAUNITFACTORY_H

#include "UnitFactory.h"

class SeaUnitFactory : public UnitFactory {
   public:
    SeaUnitFactory();
    virtual Unit* createLightUnit(std::string name) override;
    virtual Unit* createMediumUnit(std::string name) override;
    virtual Unit* createHeavyUnit(std::string name) override;
    virtual ~SeaUnitFactory();
};

#endif  // SEAUNITFACTORY_H