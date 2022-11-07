#ifndef FACTION_H
#define FACTION_H

#include <iostream>
#include <vector>

#include "../utilities/WarException.h"
#include "../utilities/json.hpp"
#include "../utilities/uuid.h"

using json = nlohmann::json;

class Alliance;
class Theatre;
class Mobilization;
/**
 * This class is the Component of the Faction Composite Design Pattern
 * Hierarchy. The pattern is used so that multiple countries may be stored in an
 * alliance. Alliances may merge and be under one big alliance.
 */
class Faction {
   protected:
    std::string name;
    std::string id;
    int morale;
    Alliance* alliance;
    std::vector<int> research;
    int baseResourceCount;
    int resourceCount;

   public:
    /**
     * Provides functionality to create a Faction object.
     *
     * @param name Name of faction
     */
    Faction(std::string name);
    /**
     * Provides functionality to get the name of a faction.
     *
     * @return std::string Name of faction
     */
    std::string getName() const;
    /**
     * Provides functionality to get the Id of a faction.
     *
     * @return std::string Id of faction
     */
    std::string getId() const;
    /**
     * Provides functionality to compare a faction to the passed in
     * faction object by comparing Ids.
     *
     * @param faction Faction to check against the current faction object
     * @return true Return if the Ids match
     * @return false Return if the Ids do not match
     */
    bool equals(Faction* faction) const;
    /**
     * Provides functionality to set the name of a faction
     *
     * @param name New name of faction
     */
    void setName(std::string name);
    /**
     * Provides functionality to set the Morale object of a faction
     *
     * @param morale New morale value
     */
    void setMorale(int morale);
    /**
     * Abstract function to be implemented in child classes.
     *
     * @param theatreResource Resources provided by dividends from theatres
     */
    virtual void generateResources(int theatreResource) = 0;
    /**
     * Provides functionality to set the baseResourceCount of a faction.
     *
     * @param baseResourceCount New baseResourceCount value
     */
    void setBaseResourceCount(int baseResourceCount);
    /**
     * Provides functionality to get the baseResourceCount of a faction.
     *
     * @return The faction's baseResourceCount
     */
    int getBaseResourceCount();
    /**
     * Abstract function to be implemented by the child classes.
     *
     * @param researchPoints Amount of research points to invest
     * @param category Research category
     */
    virtual void setResearch(int researchPoints, std::string category) = 0;
    /**
     * Abstract function to be implemented by the child classes
     *
     * @param i The index of the category in research vector
     * @return int Total research invested in research[i]
     */
    virtual int getResearch(int i) = 0;
    /**
     * Abstract function to be implemented by the child classes.
     *
     * @param index The index of the category for which to reduce the research
     * points
     */
    virtual void resetResearch(int index) = 0;
    /**
     * Provides functionality to get the Morale value
     *
     * @return int Morale value
     */
    int getMorale();
    /**
     * Abstract function to be implemented by the child classes.
     *
     * @return Alliance* Alliance pointer of a country or alliance
     */
    virtual Alliance* getAlliance() = 0;
    /**
     * Abstract function to be implemented by the child classes.
     */
    virtual void clearCasualties() = 0;
    /**
     * Provides functionality to destroy a Faction object
     */
    virtual ~Faction();
};

#endif  // FACTION_H