#ifndef SUPPORTCOMPANY_H
#define SUPPORTCOMPANY_H

#include "Entity.h"

class SupportCompany : public Entity {
protected:
    Entity * entity;
public:
    SupportCompany(Entity * entity);
    

    /**
     * Provides functionality to return the damage of the entity 
     * @return int : damage
     */

    virtual int getDamage() override;
    /**
     * Provides functionality to return the hp of the entity
     * @return int : HP
     */

    virtual int getHP() override;
    
    virtual std::string getType() const override;

    virtual std::string getId() const override;

     /**
     * Provides functionality to return the entity's name 
     * @return string : result of entity's getName()
     */

     virtual std::string getName() = 0;
     

     /**
     * Provides functionality to return the value of the entity
     * @return int : value
     */

    int getValue() const override;

    /**
     * Provides functionality to call the entity's getTheatre()
     * @return result of entity's getTheatre
     */


    virtual Theatre * getTheatre() override;

    /**
     * Provides functionality to call the entity's setTheatre()
     * @param theatre Param to be passed into entity's setTheatre
     */

    void setTheatre(Theatre *theatre) override;

    void setHP(int HP);

    void setDamage(int damage);
        /**
     * Provides functionality to reduce the entity's hp by taking damage
     * @param damage Damage used to reduce entity's hp
     * @return bool : check whether entity is dead -> entity hp ==0
     */

    bool takeDamage(int damage) override;
    /**
     * Provides functionality to call the entity's getUnitCount()
     * @return int : result of entity's getUnitCount()
     */
    int getUnitCount() const override;
    /**
     * Provides functionality to call the entity's print()
     */
    void print() override;

    /**
     * Provides functionality to call the entity's clone()
     */

    Entity *clone() override;
    /**
     * Provides functionality to call the entity's toJSON()
     * @return json : Result of entity's toJSON()
     */

    nlohmann::json toJSON() const override;
    /**
     * Provides functionality to call the entity's unitToJSON()
     * @return json : result of entity's unitToJson()
     */

    virtual nlohmann::json unitToJSON() const override;



    virtual ~SupportCompany();
};

#endif  // SUPPORTCOMPANY_H