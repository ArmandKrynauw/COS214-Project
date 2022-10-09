#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include "../Product/Unit.h";
#include <string>

class UnitFactory {
    protected:
        std::string typeOfUnit;

    public:
        UnitFactory();
        virtual Unit *createLightUnit(std::string name) = 0;
        virtual Unit *createMediumUnit(std::string name) = 0;
        virtual Unit *createHeavyUnit(std::string name) = 0;
        virtual ~UnitFactory();
};

#endif // UNITFACTORY_H