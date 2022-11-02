#ifndef ALLIANCE_H
#define ALLIANCE_H

#include "Country.h"
#include "Faction.h"

class Alliance : public Faction {
private:
    std::vector<Faction *> members;

public:
    Alliance(std::string name);

    void addCountry(Country *country);

    void removeCountry(Country *country);

     void generateResources(int theatreResource) override;

    virtual void setResearch(int researchPoints,std::string category);



    virtual Alliance *getAlliance() override;

    virtual void makeDecision()
    override;  // For each member in alliance call makeDecision()
    virtual void chooseStrategy()
    override;  // For each member in alliance call chooseStrategy()

    // virtual int getAttackPower(Theatre *theatre) override;



    json toJSON();
};

#endif  // ALLIANCE_H