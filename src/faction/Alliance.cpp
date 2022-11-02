#include "Alliance.h"

#include "Faction.h"

Alliance::Alliance(std::string name) : Faction(name) {
    name = name;
}

void Alliance::addCountry(Country *country) {
    members.push_back(country);
}

void Alliance::removeCountry(Country *country) {
    int counter = 0;
    for (Faction *p: members) {
        if (p->getName() == country->getName()) {
            members.erase(members.begin() + counter);
            break;
        }
        counter++;
    }
}

void Alliance::generateResources(int theatreResource) {
    int base = theatreResource / members.size();  //split up resource between countries


    for (Faction *faction: members) {
        faction->generateResources(base);
    }
}

int Alliance::getResourceCount() {
    resourceCount = 0;
    for (Faction *p: members) {
        baseResourceCount += p->getResourceCount();
    }
    return resourceCount;
}

void Alliance::setBaseResourceCount(int baseResourceCount) {
    this->baseResourceCount = baseResourceCount;
}

Alliance *Alliance::getAlliance() {
    return this;
}

void Alliance::makeDecision() {
    for (Faction *p: members) {
        p->makeDecision();
    }
}  // For each member in alliance call makeDecision()

void Alliance::chooseStrategy() {
    for (Faction *p: members) {
        p->chooseStrategy();
    }
}

// int Alliance::getAttackPower(Theatre *theatre) {
//     int power = 0;

//     for (Faction *faction: members) {
//         power += faction->getAttackPower(theatre);
//     }

//     return power;
// }

json Alliance::toJSON(){
    json data;
    for(Faction * f : members){
        data.push_back(f->getName());
    }
    return data;
}