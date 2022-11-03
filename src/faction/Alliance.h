#ifndef ALLIANCE_H
#define ALLIANCE_H

#include "Country.h"
#include "Faction.h"

class Alliance : public Faction {
private:
    std::vector<Faction *> members;

public:
    Alliance(std::string name);

    /**
     * Provides functionality to add a country to an alliance
     * @param country pointer to the country to be added
     */

    void addCountry(Country *country);

    /**
     * Provide functionality to remove a country from an alliance
     * 
     * @param country pointer to the country to be added
     */
    void removeCountry(Country *country);

    /**
     * Provides functionality to generate resources for each country in the alliance
     * @param theatreResource The amount of resources from theatres to divide among countries
     */

     void generateResources(int theatreResource) override;

     /**
     * Provides functionality to invest research points into research for the country
     * @param researchPoints The amount of points to invest into research
     * @param category The category to invest the research points in
     */
    
    virtual void setResearch(int researchPoints,std::string category);
     /**
     * Provides functionality to get research points of a category
     * @param i The index of the research category
     * @return Research points of current category
     */

    virtual int getResearch(int i) override;
    /**
     * Provides functionality to reduce the research points with 1000
     * @param index The index of the category for which to reduce the
     * research points
     */

    virtual void resetResearch(int index) override;

    /**
     * Provides functionality to get all the countries in the alliance
     * @return vector<Faction*> : vector of pointers to the countries in alliance
     */

    std::vector<Faction*> getMembers();

    /**
     * Provides functionality to get the current alliance
     * @return This alliance object as a pointer
     */


    virtual Alliance *getAlliance() override;

    /**
     * Provides functionality to let each country in alliance make decisions
     */

    virtual void makeDecision() override;  // For each member in alliance call makeDecision()

    /**
     * Provides functionality to let each country in alliance pick a strategy
     */

    virtual void chooseStrategy() override;  // For each member in alliance call chooseStrategy()

    // virtual int getAttackPower(Theatre *theatre) override;
    
    /**
     * Provides functionality to create a json object containing the name of all members of the alliance
     * @return Returns the json object
     */
    json toJSON();

    /**
     * Provides functionality to view the resources of each country in the alliance throught the terminal
     * 
     */
    void printResources();
};

#endif  // ALLIANCE_H