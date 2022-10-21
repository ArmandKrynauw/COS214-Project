#ifndef ARMEDFORCE_H
#define ARMEDFORCE_H

#include <vector>

#include "Entity.h"

class ArmedForce : public Entity {
   private:
    std::vector<Entity*> entities;

   public:
    ArmedForce(std::string name, std::string type);
    ~ArmedForce();
    void add(Entity* entity);
    void remove(Entity* entity);
    // std::string print() override;
    /**
     * Calculates the total damage capability of this armed force by summing
     * the damage values of all the entities contained within itself.
     *
     * @return Total damage
     */
    virtual int getDamage() const override;
    virtual int getValue() const override;
    virtual Entity* clone() override;
    void update();
};

#endif // ARMEDFORCE_H