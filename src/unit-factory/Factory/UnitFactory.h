#ifndef UNITFACTORY_H
#define UNITFACTORY_H


#include "../Product/Unit.h";
#include <iostream>
using namespace std;

class UnitFactory{
    private:
        string factoryName;
        string typeOfUnit;

    public:
        UnitFactory(string factoryName);
        virtual Unit *createLightUnit() = 0;
        virtual Unit *createMediumUnit() = 0;
        virtual Unit *createHeavyUnit() = 0;
        ~UnitFactory();
};

#endif // UNITFACTORY_H