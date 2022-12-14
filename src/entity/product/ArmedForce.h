#ifndef ARMEDFORCE_H
#define ARMEDFORCE_H

#include <vector>

#include "Entity.h"

class ArmedForce : public Entity {
   private:
    std::vector<Entity*> entities;

    ArmedForce(const ArmedForce& armedForce);

   public:
    ArmedForce(std::string name, std::string type);

    ~ArmedForce();

    void add(Entity* entity);

    void remove(Entity* entity);

    /**
     * Calculates the total damage capability of this armed force by summing
     * the damage values of all the entities contained within itself.
     *
     * @return Total damage
     */
    virtual int getDamage() const override;
    virtual int getHP() const override;
    virtual int getInitialHP() const override;

    virtual bool takeDamage(int damage) override;

    virtual int getUnitCount() const override;

    virtual int getValue() const override;

    virtual void setTheatre(Theatre* theatre) override;

    virtual void clearCasualties() override;

    virtual Entity* clone() override;

    virtual nlohmann::json toJSON() const override;

    void update();

    Entity* getEntity(int index);

    std::vector<Entity*> getEntities();
};

#endif  // ARMEDFORCE_H