#ifndef COUNTRY_H
#define COUNTRY_H

#include <unordered_map>

#include "../entity/product/ArmedForce.h"
#include "../entity/product/Entity.h"
#include "../entity/product/Unit.h"
#include "../utilities/json.hpp"
#include "Faction.h"
#include "../mobilization/Mobilization.h"
#include "../mobilization/PartialMobilization.h"

class Alliance;

using json = nlohmann::json;

class Country : public Faction {
private:
    std::unordered_map<std::string, ArmedForce *> armedForces;
    Mobilization* mobilization;

public:
    Country(std::string name);

    void joinAlliance(Alliance* a);

    void leaveAlliance();
    
    /**
     * Provides functionality to change the mobilization state of the country
     */
    void setMobilization(std::string mobilization);

    /**
     * Provides functionality to check whether country is allowed to change mobilization state
     * Will change mobilization state if allowed
     */
    void checkMobilization(std::string warState, std::string newMobilization);

    /**
     * This method is used generate new resources for each Faction after each
     * turn in the war. Newly generated resources is calculated using the
     * current mobilization and morale of a Faction.
     */
    virtual void generateResources(int theatreResource) override;

    /**
     * Provides functionality to get the resource count of country
     * 
     * @return int : The resource Count of the country
     */
    int getResourceCount();

    void setBaseResourceCount(int baseResourceCount);

    /**
     * Provides functionality to invest research points into research for the country
     * 
     * @param researchPoints The amount of points to invest into research
     * @param category The category to invest the research points in
     */
    virtual void setResearch(int researchPoints,std::string category);

    /**
     * Provides functionality to get research points of a category
     * 
     * @param i The index of the research category
     * @return Research points of current category
     */

    virtual int getResearch(int i) override;

     /**
     * Provides functionality to reduce the research points with 1000
     * 
     * @param index The index of the category for which to reduce the
     * research points
     */
    virtual void resetResearch(int index) override;

    /**
     * Provides functionality determine whether a Faction is an Alliance
     * or a Country.
     *
     * @return NULL
     */
    virtual Alliance *getAlliance() override;

    /**
     * Provides functionality to add either a Unit or an Armed Force to one of
     * the Country's existing Armed Forces. When an Entity is added its value
     * will be deducted from the Country's resources in order to simulate the
     * purchasing of Units. If insufficient resources is available then an
     * exception will get thrown.
     *
     * @param entity The Entity to add
     * @throws WarException if insufficent resources is available
     */
    void addEntity(Entity *entity);

    /**
     * Provides functionality to remove either a Unit or an Armed Force from the
     * Country's existing Armed Forces. To get hold of a specific Entity to
     * remove make use of the getEntity method.
     *
     * @param entity The entity to remove
     */
    void removeEntity(Entity *entity);

    /**
     * Provides functionality to retrieve a specific Unit or Armed Force from a
     * Country's existing Armed Forces. This enables the ability to get a handle
     * on specific Entities in order to transport them between theatres.
     *
     * @param
     */
    Entity* getEntity(const std::string &type, const int &index);

    virtual void clearCasualties() override;

    json getListOfUnits();

    int getEntityCount();

    json allUnitsToJSON();

    /**
     * @brief Check if Country has units in any of the zones
     * 
     * @return true Return true if country has at leat 1 unit in any zone
     * @return false Return false if country has no units in any zones
     */
    bool checkForArmedForces();

    /**
     * @brief Check if Country is in an Alliance
     * 
     * @return true Return if country is in alliance
     * @return false Return if country is not in alliance
     */
    bool inAlliance();

    virtual std::string getMobilization() override;

    json researchToJSON();

    virtual ~Country();
};

#endif  // COUNTRY_H