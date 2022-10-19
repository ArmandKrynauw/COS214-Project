#include "SeaUnitFactory.h"
#include "../Product/SeaUnitLight.h"
#include "../Product/SeaUnitMedium.h"
#include "../Product/SeaUnitHeavy.h"

SeaUnitFactory::SeaUnitFactory() : UnitFactory() {
    // typeOfUnit = "Sea";
}

Unit *SeaUnitFactory::createLightUnit(std::string name) {
    // pass name as a parameter to SeaUnitLight constructor?
    return new SeaUnitLight();
}

Unit *SeaUnitFactory::createMediumUnit(std::string name) {
    // pass name as a parameter to SeaUnitMedium constructor?
    return new SeaUnitMedium();
}

Unit *SeaUnitFactory::createHeavyUnit(std::string name) {
    // pass name as a parameter to SeaUnitHeavy constructor?
    return new SeaUnitHeavy();
}

SeaUnitFactory::~SeaUnitFactory() {
}