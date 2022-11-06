#include "SupportCompany.h"

SupportCompany::SupportCompany(Entity* entity) {
    this->entity = entity;
}

SupportCompany::SupportCompany(const SupportCompany& supportCompany) {
    this->entity = entity->clone();
}

std::string SupportCompany::getType() const{
    return entity->getType();
}

std::string SupportCompany::getId() const{
    return entity->getId();
}

int SupportCompany::getDamage() const { 
    return entity->getDamage(); 
}

int SupportCompany::getHP() const {
    return entity->getHP();
}

int SupportCompany::getInitialHP() const {
    return entity->getInitialHP();
}

int SupportCompany::getValue() const {
    return entity->getValue();
}

bool SupportCompany::takeDamage(int damage) {
    return entity->takeDamage(damage);
}

int SupportCompany::getUnitCount() const {
    return entity->getUnitCount();
}

void SupportCompany::setTheatre(Theatre *theatre) {
    entity->setTheatre(theatre);
}

void SupportCompany::clearCasualties() {
    entity->clearCasualties();
}

nlohmann::json SupportCompany::toJSON() const {
    return json{
            {"name", getName()},
            {"type", getType()},
            {"initialHP", getInitialHP()},
            {"currentHP", getHP()},
            {"damage",  getDamage()},
            {"theatre", (entity->getTheatre()) ? entity->getTheatre()->getName() : "Evacuated"},
            {"id", getId()}
    };
    return entity->toJSON();
}

SupportCompany::~SupportCompany() {
    delete entity;
}

Theatre* SupportCompany::getTheatre() {
    return entity->getTheatre();
}

void SupportCompany::setHP(int hp) {
    return entity->setHP(hp);
}

void SupportCompany::setDamage(int damage) {
    return entity->setDamage(damage);
}
