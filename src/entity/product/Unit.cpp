#include "Unit.h"

Unit::Unit(std::string name, std::string type, int HP, int damage) : Entity(name, type) {
    this->HP = HP;
    this->damage = damage;
}

int Unit::getHP() const {
    return HP;
}

int Unit::getDamage() const {
    return damage;
}

void Unit::setHP(int HP) {
    this->HP = HP;
}

void Unit::setDamage(int damage) {
    this->damage = damage;
}

void Unit::takeDamage(int damage) {

}

std::string Unit::print() {
    std::cout << "Printing for testing purposes" << std::endl;
    
}

Unit::~Unit() { }