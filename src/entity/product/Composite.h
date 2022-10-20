#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>

#include "Entity.h"

class Composite : public Entity {
   private:
    std::vector<Entity*> units;

   public:
    Composite(std::string name, std::string type);
    ~Composite();
    void add(Entity* entity);
    void remove(int a);
    // std::string print() override;
    /**
     * Calculates the total damage capability of this armed force by summing
     * the damage values of all the entities contained within itself.
     *
     * @return Total damage
     */
    virtual int getDamage() const override;
    virtual Entity* clone() override;
    void update();
};

#endif  // COMPOSITE_H