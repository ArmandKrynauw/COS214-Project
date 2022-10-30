#ifndef FACTION_H
#define FACTION_H

#include <iostream>
#include <vector>

#include "../utilities/WarException.h"
#include "../utilities/uuid.h"

class Alliance;
class Theatre;
class Mobilization;

class Faction {
   protected:
    std::string name;
    std::string id;
    int morale;
    int baseResourceCount;
    int resourceCount;
    Mobilization* mobilization;

   public:
    Faction(std::string name);
    std::string getName();
    std::string getId() const;
    bool equals(Faction* faction) const;
    void setName(std::string name);
    void decreaseMoraleBy(int amount);
    void increaseMoraleBy(int amount);

    /**
     * This method is used generate new resources for each Faction after each
     * turn in the war. Newly generated resources is calculated using the
     * current mobilization and morale of a Faction.
     */
    virtual void generateResources() = 0;
    virtual int getResourceCount() = 0;
    /**
     * This method is used to sum all the attack power of a faction for a
     * specific theatre.
     *
     * @param theatre Theatre to sum attack power for
     * @return Sum of attack power
     */
    virtual int getAttackPower(Theatre* theatre) = 0;
    virtual void setBaseResourceCount(int baseResourceCount) = 0;
    /**
     * This method is used to determine wether a Faction is a Country or an
     * Alliance
     */
    virtual Alliance* getAlliance() = 0;

    // Turn
    virtual void makeDecision() = 0;
    virtual void chooseStrategy() = 0;
};

#endif  // FACTION_H