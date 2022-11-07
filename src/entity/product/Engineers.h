#ifndef Engineers_H
#define Engineers_H

#include "SupportCompany.h"

class Engineers : public SupportCompany {
   private:
    Engineers(const Engineers& engineers);

   public:
    Engineers(Entity* unit);

    /**
     * Provides functionality to calculate the result of the entity's Damage
     * *1.25
     * @return int : damage
     */
    virtual int getDamage() const override;

    /**
     * Provides functionality to return the entity's name abbreviated with -EG
     * @return string : result of entity's getName() + -EG
     */
    virtual std::string getName() const override;

    virtual Entity* clone() override;

    virtual ~Engineers();
};

#endif  // Engineers_H