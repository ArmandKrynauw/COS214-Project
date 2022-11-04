#include "SupportCompany.h"

SupportCompany::SupportCompany(Entity* entity) {
    this->entity = entity;
}

std::string SupportCompany::getType() const{
    return entity->getType();
}

std::string SupportCompany::getId() const{
    return entity->getId();
}


int SupportCompany::getDamage() { 
    return entity->getDamage(); 
}

int SupportCompany::getHP() {
    return entity->getHP();
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

void SupportCompany::print() {
    entity->print();
}

void SupportCompany::setTheatre(Theatre *theatre) {
    entity->setTheatre(theatre);
}

Entity *SupportCompany::clone() {
    return entity->clone();
}

nlohmann::json SupportCompany::toJSON() const {
    return entity->toJSON();
}

SupportCompany::~SupportCompany() {
    delete entity;
}

// std::string SupportCompany::getName(){
//    return entity->getName();
// }



nlohmann::json SupportCompany::unitToJSON() const{
    return entity->unitToJSON();
}

Theatre* SupportCompany::getTheatre(){
    return entity->getTheatre();
}

void SupportCompany::setHP(int hp){
    return entity->setHP(hp);
}

void SupportCompany::setDamage(int damage){
    return entity->setDamage(damage);
}






