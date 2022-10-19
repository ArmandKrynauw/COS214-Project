#include "AirUnitFactory.h"
#include "../Product/AirUnitLight.h"
#include "../Product/AirUnitMedium.h"
#include "../Product/AirUnitHeavy.h"

AirUnitFactory::AirUnitFactory() : UnitFactory(){
    typeOfUnit = "Air";
}

Unit *AirUnitFactory::createLightUnit(std::string name) {
    // pass name as a parameter to AirUnitLight constructor?
    return new AirUnitLight();
}

Unit *AirUnitFactory::createMediumUnit(std::string name) {
    // pass name as a parameter to AirUnitMedium constructor?
    return new AirUnitMedium();
}

Unit *AirUnitFactory::createHeavyUnit(std::string name) {
    // pass name as a parameter to AirUnitHeavy constructor?
    return new AirUnitHeavy();
}

AirUnitFactory::~AirUnitFactory() {
}
