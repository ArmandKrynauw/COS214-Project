#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity {
protected:
    int HP;
    int damage;
    int value;
    Theatre *theatre;
    int initialHP;

public:

    Unit();

    Unit(std::string name, std::string type, int HP, int damage, int value);
    
    /**
     * Provides functionality to return the current damage of the Unit
     * @return int : Damage of Unit
    */
    virtual int getDamage() const override;
    /**
     * Provides functionality to return the current HP of the Unit
     * @return int : HP of Unit
    */

    virtual int getHP() const override;
     /**
     * Provides functionality to return the value  of the Unit
     * @return int : value of Unit
    */

    virtual int getInitialHP() const override;

     /**
     * Provides functionality to return the Value of the unit
     * @return int : The value of the unit
    */

    virtual int getValue() const override;
   /**
     * Provides functionality to return the Theatre the Unit is stored in
     * @return Theatre* : Theatre Unit is stored in
    */

    

    Theatre *getTheatre();

    /**
     * Provides functionality to set the theatre pointer to a theatre
     * @param theatre The theatre that Unit will now point to
    */

    virtual void setTheatre(Theatre *theatre) override;

    /**
     * Provides functionality to set the HP of the unit
     * @param HP The new HP that the unit will be set to
    */

    void setHP(int HP);

    /**
     * Provides functionality to set the damage of the unit
     * @param damage The new damage that the unit will be set to
    */

    void setDamage(int damage);

    /**
     * Provides functionality to reduce hp by taking damage
     * @param damage The damage that will be used to reduce hp
     * @return bool : check whether unit is dead -> hp==0
    */

    virtual bool takeDamage(int damage) override;

    /**
     * Provides functionality to return the unit Count of the Unit
     * @return int : The unit count of the unit
     */
    virtual int getUnitCount() const override;

    /**
     * Provides functionality to display the unit's name, hp and damage
    */

    void print();


    /**
     * Provides functionality to clone an existing unit
     * @return Entity pointer to new clone
    */
    virtual Entity *clone() = 0;
    /**
     * Provides functionality to parse data of the unit into json
     * @return json object of format:
     * {
            {"name",    name},
            {"type",    type},
            {"hp",      HP},
            {"damage",  damage},
            {"theatre", theatre_name}
    }
    */
    virtual nlohmann::json toJSON() const override;
     /**
     * Provides functionality to parse data of the unit into json
     * @return json object of format:
     * {"name",    name},
       {"type",    type},
       {"initialHP",  initialHP},
       {"damage",  damage},
       {"currentHP", HP}
        }
    */

    virtual nlohmann::json unitToJSON() const override;

    /**
     * Provides functionality to destruct current unit
    */
    virtual ~Unit();
};

#endif
