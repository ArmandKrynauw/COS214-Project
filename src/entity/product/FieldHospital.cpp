#include "FieldHospital.h"

FieldHospital::FieldHospital(Entity* entity) : SupportCompany(entity) {
    entity->setName(entity->getName() + "-FH");
}

int FieldHospital::getDamage() {
    return SupportCompany::getDamage();
}

int FieldHospital::getHP() {
    return entity->getHP() * 1.25;
}

std::string FieldHospital::getName(){
    return entity->getName();
}

FieldHospital::~FieldHospital() {

}