#ifndef SUPPORTCOMPANY_H
#define SUPPORTCOMPANY_H

#include "Entity.h"


class SupportCompany : public Entity {
   protected: 
   Entity* entity;
   public:
    SupportCompany(Entity* entity);
    virtual int getDamage()  override ;
    virtual int getHP()  override;
    int getValue() const  override ;
    bool takeDamage(int damage)  override ;
    int getUnitCount()  const  override ;
    void print() override;
    void setTheatre(Theatre* theatre)override;
    Entity* clone() override;
    nlohmann::json toJSON()  const override ;
    virtual ~SupportCompany();
};

#endif  // SUPPORTCOMPANY_H