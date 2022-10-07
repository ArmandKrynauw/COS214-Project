#include "party.h"

Party::Party(std::string name){

    this->name = name;
}

std::string Party::getName(){

    return name;
}

void Party::setName(std::string name){

        this->name = name;
}