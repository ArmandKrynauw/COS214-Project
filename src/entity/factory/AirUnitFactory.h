#ifndef AIRUNITFACTORY_H
#define AIRUNITFACTORY_H

#include "UnitFactory.h"

class AirUnitFactory : public UnitFactory {
   public:
    AirUnitFactory();
    /**
     * Provides functionality to create a new Light air unit
     * @param name Name of new Light air unit
     * @return Unit pointer to new Light air unit object
     */

    virtual Unit* createLightUnit(std::string name) override;
    /**
     * Provides functionality to create a new Medium air unit
     * @param name Name of new Medium air unit
     * @return Unit pointer to new Medium air unit object
     */

    virtual Unit* createMediumUnit(std::string name) override;
    /**
     * Provides functionality to create a new Heavy air unit
     * @param name Name of new Heavy air unit
     * @return Unit pointer to new Heavy air unit object
     */

    virtual Unit* createHeavyUnit(std::string name) override;

    virtual ~AirUnitFactory();
};

#endif  // AIRUNITFACTORY_H