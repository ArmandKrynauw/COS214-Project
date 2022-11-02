#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../utilities/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"

class Entity;

class Zone {
protected:
    std::string name;
    std::string id;
    std::vector<Entity *> entities;


public:
    Zone(std::string name);

    /**
     * Provides functionality to get the total damage of the entity in zone
     * @return int : TotalDamage of units in zone
    */

    int getTotalDamage();

    /**
     * Provides functionality to add an entity to the zone
     * @param entity pointer to new entity to be added
    */

    void addEntity(Entity *entity);

     /**
     * Provides functionality to remove an entity from the zone
     * @param id Id of the entity to be removed from the zone as a string
     * @return Entity* : pointer to the entity that was removed
     */

    Entity *removeEntity(std::string id);

    /**
     * Provides functionality to get the name of the zone
     * @return string : Name of zone
     */

    std::string getName() const;

    /**
     * Provides functionality to get the number of entities in the zone
     * @return int : Number of entities in the zone
     */

    int getUnitCount() const;

    /**
     * Provides functionality to get all the entities in the zone
     * @return vector<Entity *> : a vector containing all the entities
     */

    std::vector<Entity *> getEntities();

    /**
     * Provides functionality to get the type of the zone
     * @return string : Type of the zone
     */

    virtual std::string getType() = 0;

    virtual ~Zone();

    // =============== Template Method ===============

    /**
     * Provides functionality to reduce the hp of entities in the zone
     * @param damage The amount of damage to be dished out between units
     */
    void takeDamage(int damage);

private:
    /**
     * Provides functionality to get the divisor used in takeDamage()
     * @return int : Divisor to be used in takeDamage()
     */
    virtual int getDamageDivisor() = 0;

};

#endif // ZONE_H