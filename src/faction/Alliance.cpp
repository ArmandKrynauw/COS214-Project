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

void Alliance::setResearch(int researchPoints,std::string category)
{
    
    
    // Faction::setResearch(researchPoints,category);
    // this->resourceCount -= researchPoints;

    // if(research.at(0)>=1000)
    // {
    //     research.at(0) -= 1000;
    //     baseResourceCount = baseResourceCount*1.2;
        
    // }
    // else if(research.at(1)>=1000)
    // {
    //     research.at(1) -= 1000;
    //     morale = morale*1.2;
    // }


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