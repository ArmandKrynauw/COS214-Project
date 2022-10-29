#include "Unit.h"

Unit::Unit(std::string name, std::string type, int HP, int damage, int value)
    : Entity(name, type), HP(HP), damage(damage), value(value) {
}

int Unit::getHP() const {
    return HP;
}

int Unit::getDamage() const {
    return damage;
}

int Unit::getValue() const {
    return value;
}

void Unit::setHP(int HP) {
    this->HP = HP;
}

void Unit::setDamage(int damage) {
    this->damage = damage;
}

bool Unit::takeDamage(int damage) {
    this->HP = this->HP - damage;
    if(this->HP<=0) return true;
    else
    return false;
}

void Unit::print() {
    std::cout << this->name + " HP: " + std::to_string(this->HP) + " Damage: " + std::to_string(this->damage) << std::endl;
}

std::string Unit::getName() const {
    return name;
}

Unit::~Unit() {}