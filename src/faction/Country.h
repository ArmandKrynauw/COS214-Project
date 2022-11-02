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

using json = nlohmann::json;

class Country : public Faction {
private:
    std::unordered_map<std::string, ArmedForce *> armedForces;
    Mobilization* mobilization;

public:
    Country(std::string name);

    /**
     * Provides functionality to change the mobilization state of the country
     * @return void
     */

    void  setMobilization(std::string mobilization);

    void checkMobilization(std::string warState, std::string newMobilization);

    /**
     * This method is used generate new resources for each Faction after each
     * turn in the war. Newly generated resources is calculated using the
     * current mobilization and morale of a Faction.
     */
    void generateResources();

    int getResourceCount();

    void setBaseResourceCount(int baseResourceCount);

    virtual int getAttackPower(Theatre *theatre) override;

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
     *
     */
    Entity *getEntity(const std::string &type, const int &index);

    virtual void makeDecision() override;

    virtual void chooseStrategy() override;

    void printUnits();

    json getListOfUnits();

    json removeCasualties();

    int getEntityCount();

    json allUnitsToJSON();

    bool checkForArmedForces();

    /**
     * @brief Check if Country is in an Alliance
     * 
     * @return true return if country is in alliance
     * @return false return if country is not in alliance
     */
    bool inAlliance();
};

#endif  // COUNTRY_H