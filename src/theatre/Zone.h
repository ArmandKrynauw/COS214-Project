#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../utilities/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"

class Entity;
/**
 * This class is the AbstractClass in the Template Method Design Pattern. This pattern is used to house different
 * types of entities being "land", "sea" or "air". Each different zone will have a different divisor dependant on
 * the type of entities it holds.
 */
class Zone {
    protected:
        std::string name;
        std::string id;
        std::vector<Entity *> entities;
    public:
        /**
         * Provides functionality to create a Zone object.
         * 
         * @param name Name of zone
         */
        Zone(std::string name);
        /**
         * Provides functionality to get the total damage of
         * all entities in the zone.
         * 
         * @return Total damage of all entities in zone
         */
        int getTotalDamage();
        /**
         * Provides functionality to add an entity to the zone
         * 
         * @param entity Entity pointer to be added to the entities vector
         */
        void addEntity(Entity *entity);
        /**
         * Provides functionality to remove an entity from the zone
         * 
         * @param id Id of the entity to be removed from the zone
         * @return  Entity pointer that was removed from the entities vector
         */
        Entity *removeEntity(std::string id);
        /**
         * Provides functionality to get the name of the zone
         * 
         * @return  Name of zone
         */
        std::string getName() const;
        /**
         * Provides functionality to get the number of entities in the zone
         * 
         * @return  Number of entities in the zone
         */
        int getUnitCount() const;
        /**
         * Provides functionality to get entities vector
         * 
         * @return  std::vector<Entity *> containing all the entities in the zone
         */
        std::vector<Entity *> getEntities();
        /**
         * Abstract function to be implemented in the child classes.
         * 
         * @return Type of the zone
         */
        virtual std::string getType() = 0;
        /**
         * Provide functionality to destroy a Zone object.
         */
        virtual ~Zone();

        // =============== Template Method ===============
        /**
         * Provides functionality to reduce the hp of entities in the zone
         * The function is the templateMethod() of the Zone Template Method Design Pattern.
         * 
         * @param damage The amount of damage to be dished out between units
         */
        void takeDamage(int damage);

    private:
        /**
         * Abstract function to be implemented in the child classes.
         * 
         * @return Divisor to be used in the templateMethod()
         */
        virtual int getDamageDivisor() = 0;
};

#endif // ZONE_H