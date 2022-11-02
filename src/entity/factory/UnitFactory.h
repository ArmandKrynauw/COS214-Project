#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include <string>

#include "../product/Unit.h"

class UnitFactory {
protected:
    std::string type;

public:
    UnitFactory();
    /**
     * Provides functionality to create a new light unit
     * @param name Name of new light unit
     * @return Unit pointer to new light unit object
    */

    virtual Unit *createLightUnit(std::string name = "") = 0;
    /**
     * Provides functionality to create a new medium  unit
     * @param name Name of new medium  unit
     * @return Unit pointer to new medium  unit object
    */
    virtual Unit *createMediumUnit(std::string name = "") = 0;
    /**
     * Provides functionality to create a new heavy  unit
     * @param name Name of new heavy  unit
     * @return Unit pointer to new heavy  unit object
    */
    virtual Unit *createHeavyUnit(std::string name = "") = 0;

    virtual ~UnitFactory();
};

#endif  // UNITFACTORY_H