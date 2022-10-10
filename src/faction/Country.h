#ifndef COUNTRY_H
#define COUNTRY_H
#include "Faction.h"

class Unit;

class Country : public Faction {
   private:
    std::vector<Unit*> units;

   public:
    Country(std::string name);
    virtual void generateResources() override;
    virtual int getResourceCount() override;
    virtual void setResourceCount(int baseResourceCount) override;
    virtual int getAttackPower(Theatre* theatre) override;
    virtual Alliance* getAlliance() override;

    void addUnit(Unit* unit);
    void removeUnit(Unit* unit);

    virtual void makeDecision() override;
    virtual void chooseStrategy() override;
};

#endif  // COUNTRY_H