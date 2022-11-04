#include "FieldHospital.h"

FieldHospital::FieldHospital(Entity* entity) : SupportCompany(entity) { }

bool FieldHospital::takeDamage(int damage) {
    return SupportCompany::takeDamage(damage * 0.75);
}

std::string FieldHospital::getName() const {
    return entity->getName() + "-FH";
}

FieldHospital::~FieldHospital() { }