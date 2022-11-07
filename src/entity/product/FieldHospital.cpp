#include "FieldHospital.h"

FieldHospital::FieldHospital(Entity* entity) : SupportCompany(entity) { }

FieldHospital::FieldHospital(const FieldHospital& fieldHospital) : SupportCompany(fieldHospital) {}

bool FieldHospital::takeDamage(int damage) {
    return SupportCompany::takeDamage(damage * 0.75);
}

std::string FieldHospital::getName() const {
    return entity->getName() + "-FH";
}

Entity* FieldHospital::clone() {
   return new FieldHospital(*this);
}

FieldHospital::~FieldHospital() { }