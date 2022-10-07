#include "alliance.h"
#include "party.h"

Alliance::Alliance(std::string name) : Party(name){
    name = name;
}

void Alliance::addCountry(Country* country){

    members.push_back(country);
}

void Alliance::removeCountry(Country* country){

    int counter = 0;
    for(Party * p : members){

        if(p->getName() == country->getName()){

            members.erase(members.begin() + counter);
            break;
        }
        counter++;
    }
}
//Recalculate resources as may be affected to war, set attribute and return it
int Alliance::getResourceCount(){

    int totalResources = 0;
    for(Party * p : members){

        totalResources += p->getResourceCount();
    }
    return setResourceCount(totalResources);
}

int Alliance::setResourceCount(int resourceCount){

    this->resourceCount = resourceCount;
    return this->resourceCount;
}

Alliance* Alliance::getAlliance(){

    return this;
}

void Alliance::makeDecision(){

    for(Party * p : members){

        p->makeDecision();
    }
}   //For each member in alliance call makeDecision()

void Alliance::chooseStrategy(){

    for(Party * p : members){

        p->chooseStrategy();
    }
}