#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

#include "../../theatre/Theatre.h"
#include "../../utilities/json.hpp"

class Entity {
protected:
    std::string name;
    std::string id;
    std::string type;

    Entity();
    Entity(const Entity& unit);

public:
    Entity(std::string name, std::string type);

    virtual std::string getName() const;

    /**
     * Provides functionality to return the current damage of the Unit
     * @return int : Damage of Unit
    */
    virtual int getDamage() const = 0;

    /**
     * Provides functionality to return the current HP of the Unit
     * @return int : HP of Unit
    */
    virtual int getHP() const = 0;

    /**
     * Provides functionality to return the Initial HP of the Unit
     * @return int : Initial HP of Unit
    */
    virtual int getInitialHP() const = 0;
    /**
     * Provides functionality to return the Value of the unit
     * @return int : The value of the unit
    */

    virtual int getValue() const = 0;
    /**
     * Provides functionality to return the type of the unit
     * @return string : The type of the unit
    */

    virtual std::string getType() const;
    /**
     * Provides functionality to return the id of the unit
     * @return string : The id of the unit
    */

    virtual std::string getId() const;

    /**
     * Provides functionality to set the name of unit
     * @param name The string that the unit's name will be set to
    */

    void setName(std::string name);

    /**
     * Provides functionality to return the Theatre the Unit is stored in
     * @return Theatre* : Theatre Unit is stored in
    */
    virtual Theatre* getTheatre();

    /**
     * Provides functionality to reduce hp by taking damage
     * @param damage The damage that will be used to reduce hp
     * @return bool : check whether unit is dead -> hp==0
    */
    virtual bool takeDamage(int damage) = 0;
    
    /**
     * Provides functionality to return the unit Count of the Unit
     * @return int : The unit count of the unit
     */
    virtual int getUnitCount() const = 0;

    /**
     * Provides functionality to set the damage of the unit
     * @param damage The new damage that the unit will be set to
    */
    virtual void setDamage(int damage);

    /**
     * Provides functionality to set the theatre pointer to a theatre
     * @param theatre The theatre that Unit will now point to
    */
    virtual void setTheatre(Theatre *theatre) = 0;

    /**
     * Provides functionality to remove all entity's that have died
    */
    virtual void clearCasualties() = 0;

    /**
     * Provides functionality to clone an existing unit
     * @return Entity pointer to new clone
    */
    virtual Entity* clone() = 0;

    /**
     * Provides functionality to parse data of the unit into json
     * @return json object of format:
     * {
            {"name",    name},
            {"type",    type},
            {"initialHP", initialHP},
            {"currentHP", HP},
            {"damage",  damage},
            {"theatre", if (theatre) theatre->getName() else "Evacuated"},
            {"id", id}
        }
    */
    virtual nlohmann::json toJSON() const = 0;

    /**
     * Provides functionality to set the HP of the unit
     * @param HP The new HP that the unit will be set to
    */

    virtual void setHP(int hp);

    virtual ~Entity();
};

#endif  // ENTITY_H