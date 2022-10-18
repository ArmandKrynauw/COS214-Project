#include "Unit.h"

Unit::Unit(int HP, int damage) {
    this->HP = HP;
    this->damage = damage;
}
int Unit::getHP(){
    return HP;
}
int Unit::getDamage(){
    return damage;
}
void Unit::setHP(int HP){
    this->HP = HP;
}
void Unit::setHP(int damage){
    this->damage = damage;
}
std::string Unit::print(){
    cout << "Printing for testing purposes" << endl;
    
}
Unit::~Unit(){
    this->HP = 0;
    this->damage = 0;
}