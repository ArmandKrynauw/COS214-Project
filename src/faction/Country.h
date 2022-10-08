#ifndef COUNTRY_H
#define COUNTRY_H
#include "Faction.h"

class Country : public Faction {

  public:
    Country(std::string name);
    virtual int getResourceCount() override;
    virtual void setResourceCount(int baseResourceCount) override;
    virtual Alliance* getAlliance() override;

    virtual void makeDecision() override;
    virtual void chooseStrategy() override; //
};

#endif // COUNTRY_H