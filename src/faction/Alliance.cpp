#include "Alliance.h"

#include "Faction.h"

Alliance::Alliance(std::string name) : Faction(name) {
    name = name;
}

void Alliance::addCountry(Country *country) {
    members.push_back(country);
    country->joinAlliance(this);
}

void Alliance::removeCountry(Country *country) {
    int counter = 0;
    for (Faction *p: members) {
        if (p->getName() == country->getName()) {
            ((Country*)members[counter])->leaveAlliance();
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

void Alliance::clearCasualties() {
    for (Faction* faction : members) {
        faction->clearCasualties();
    }
}

std::vector<Faction*> Alliance::getMembers() {
        return members;
}

void Alliance::setResearch(int researchPoints,std::string category) {
    Faction::setResearch(researchPoints,category);    
}

int Alliance::getResearch(int i) {
    return research[i];
}

void Alliance::resetResearch(int index) {
    research[index] -= 500;
}

json Alliance::toJSON() {
    json data = json::array();
    for(Faction * f : members){
        data.push_back(f->getName());
    }
    return data;
}

Alliance::~Alliance() {}