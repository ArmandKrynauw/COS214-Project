#ifndef FACTION_H
#define FACTION_H

#include <iostream>
#include <vector>

class Unit;
class Alliance;
class Theatre;
class Mobilization;

class Faction {
  protected:
    std::string name;
    int morale;
    std::vector<Unit*> units;
    int baseResourceCount;
    int resourceCount;
    Mobilization* mobilization;
    std::vector<Theatre*> theatres;

  public:
    Faction(std::string name);
    std::string getName();
    void setName(std::string name);
    void decreaseMoraleBy(int amount);
    void increaseMoraleBy(int amount);
    /**
     * This method is used generate new resources for each Faction after
     * each turn in the war. Newly generated resources is calculated using
     * the current mobilization and morale of a Faction.
     */
    void generateResources();
    virtual int getResourceCount() = 0;
    virtual void setResourceCount(int baseResourceCount) = 0;
    virtual Alliance* getAlliance() = 0;

    // Turn
    virtual void makeDecision() = 0;
    virtual void chooseStrategy() = 0;
};

#endif // FACTION_H