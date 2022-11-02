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
    Mobilization *mobilization;
    Alliance* alliance;
    std::vector<int> research;
    int baseResourceCount;
    int resourceCount;


public:
    Faction(std::string name);

    std::string getName();



    std::string getId() const;

    bool equals(Faction *faction) const;

    void setName(std::string name);


    
    /**
     * Set the Morale object
     * 
     * @param morale New morale value
     */
    void setMorale(int morale);

    /**
     * This method is used generate new resources for each Faction after each
     * turn in the war. Newly generated resources is calculated using the
     * current mobilization
     * @param theatreResource Resources provided by dividends from theatres
     */
    virtual void generateResources(int theatreResource)=0;
    /**
     * Provides functionality to set the baseResourceCount of a faction
     * @param baseResourceCount The value to set baseResourceCount to
     */
    
    void setBaseResourceCount(int baseResourceCount);
    /**
     * Provides functionality to get the baseResourceCount of a faction
     * @return returns the faction's baseResourceCount
     */

    int getBaseResourceCount();
    /**
     * Provides functionality to invest  researchPoints for a faction
     * @param researchPoints The amount of researchpoints to invest
     * @param category The category to invest the researchPoints in
     */

    virtual void setResearch(int researchPoints,std::string category)=0;
    /**
     * Provides functionality to get the Research points for a category
     * @param i The index of the category to get ressearchPoints from
     * @return int : the researchPoints of the category passed in
     */

    virtual int getResearch(int i)=0;
    /**
     * Provides functionality to reduce the research points with 1000
     * @param index The index of the category for which to reduce the
     * research points
     */

    virtual void resetResearch(int index) = 0;

    /**
     * Get the Morale object
     * 
     * @return int Return morale value
     */
    int getMorale();
    

    /**
     * This method is used to sum all the attack power of a faction for a
     * specific theatre.
     *
     * @param theatre Theatre to sum attack power for
     * @return Sum of attack power
     */
    // virtual int getAttackPower(Theatre *theatre) = 0;


    /**
     * This method is used to determine wether a Faction is a Country or an
     * Alliance
     */
    virtual Alliance *getAlliance() = 0;

    // Turn
    virtual void makeDecision() = 0;

    virtual void chooseStrategy() = 0;

    virtual ~Faction();
};

#endif  // FACTION_H