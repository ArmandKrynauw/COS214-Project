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

/**
 * This class is the Leaf of the Faction Composite Design Pattern Hierarchy. The country stores entities, has an economy
 * and may be join/leave and alliance.
 */
class Country : public Faction {
    private:
        std::unordered_map<std::string, ArmedForce *> armedForces;
        Mobilization* mobilization;
    public:
        /**
         * Provides functionality to create a Country object.
         * 
         * @param name Name of Country
         */
        Country(std::string name);
        /**
         * Provides functionality for a Country to join an alliance
         * by setting it alliance pointer to the passed in pointer.
         * 
         * @param a Alliance that the Country will join
         */
        void joinAlliance(Alliance* a);
        /**
         * Provides functionality for a Country to leave an alliance
         * by removing the country from the alliance and then setting the alliance pointer to NULL.
         */
        void leaveAlliance();
        /**
         * Provides functionality to change the mobilization state of the country
         * 
         * @param mobilization Mobilization level
         */
        void setMobilization(std::string mobilization);
        /**
         * Provides functionality to change the mobilization of a country by checking the escalation of the war
         * and using the Mobilization state pattern to decide if the mobilization of the country can change.
         * 
         * @param warState Current Escalation of war
         * @param newMobilization Mobilization level the country wants to reach
         */
        void checkMobilization(std::string warState, std::string newMobilization);
        /**
         * This method is used generate new resources for each Faction after each
         * turn in the war. Newly generated resources are calculated using the
         * current mobilization and morale of a Faction. The total resources from theatres is
         * then added.
         * 
         * @param theatreResource Total resources from all theatres
         */
        virtual void generateResources(int theatreResource) override;
        /**
         * Provides functionality to get the resourceCount of country.
         * 
         * @return int ResourceCount of the country
         */
        int getResourceCount();
        /**
         * Provides functionality to set the baseResourceCount of a country
         * 
         * @param baseResourceCount New baseResourceCount
         */
        void setBaseResourceCount(int baseResourceCount);
        /**
         * Provides functionality to invest research points into research for the country
         * If the country is in an alliance the the resources will be invested into the alliances research vector.
         * 
         * If the category that is invested in meets the goal of >= 500 points, the category is decreased by 500 points
         * and the country is given the appropriate advantage.
         * 
         * @param researchPoints Total points to research
         * @param category Category to research
         */
        virtual void setResearch(int researchPoints,std::string category) override;
        /**
         * Provides functionality to get current research of a category at
         * research[i]
         * 
         * @param i The index of the research category
         * @return Research points of current category
         */
        virtual int getResearch(int i) override;
        /**
         * Provides functionality to reset research[i] by reducing 500 points.
         * 
         * @param index The index of the category for which to reduce the research points
         */
        virtual void resetResearch(int index) override;
        /**
         * Provides functionality to get the alliance of a country
         *
         * @return Alliance* Return if country is in an alliance
         * @return NULL Return if country is not in an alliance
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
        /**
         * Provides functionality to  destroy all entity objects in a
         * country's armedForce if they are dead i.e. their hp is 0.
         */
        virtual void clearCasualties() override;
        /**
         * Provides functionality to return entities across all the country's armedForces per theatre
         * in JSON format.
         * 
         * @return json JSON array of theatres containing JSON arrays of entities as JSON objects
         */
        json getListOfUnits();
        /**
         * Provides functionality to return total entities across all the country's
         * armedForces in JSON format.
         * 
         * @return int Total entities owned by a country
         */
        int getEntityCount();
        /**
         * Provides functionality to traverse all armedForces owned by a country and get the JSON format
         * of each entity in said armedForces.
         * 
         * @return json JSON array of entity JSON objects
         */
        json allUnitsToJSON();
        /**
         * Provides functionality to check if a country has units in any of the zones
         * 
         * @return true Return if country has at least 1 unit in any zone
         * @return false Return if country has no units in any zones
         */
        bool checkForArmedForces();
        /**
         * Provides functionality to check if a country is in an Alliance
         * If the a country's alliance* is NULL it is not currently in an
         * alliance otherwise it is in an alliance.
         * 
         * @return true Return if country is in alliance
         * @return false Return if country is not in alliance
         */
        bool inAlliance();
        /**
         * Provides functionality to get to get state of a country's mobilization.
         * 
         * @return std::string Mobilization state
         */
        virtual std::string getMobilization();
        /**
         * Provides functionality to return the current research of a country in JSON format.
         * (e.g. {"name": "Germany", "industryCurrent": 0,"propagandaCurrent": 0, "researchGoal": 500})
         * 
         * @return json JSON Object
         */
        json researchToJSON();
        /**
         * Provides functionality to return an armed force of the passed in type.
         * The armed force may be of type "land", "sea" or "air".
         * 
         * @param type Type of ArmedForce
         * @return ArmedForce* Country's ArmedForce of type "type"
         */
        ArmedForce * getArmedForce(std::string type);
        /**
         * Provide functionality to destroy a Country object.
         */
        virtual ~Country();
};

#endif  // COUNTRY_H