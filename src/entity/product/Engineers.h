#ifndef Engineers_H
#define Engineers_H

#include "SupportCompany.h"


class Engineers : public SupportCompany {
public:
    Engineers(Entity *entity);
    /**
     * Provides functionality to calculate the result of the entity's Damage *1.25 
     * @return int : damage
     */
    int getDamage() override;
    /**
     * Provides functionality to return the entity's hp
     * @return int : HP
     */

    int getHP() override;

    virtual ~Engineers();
};

#endif  // Engineers_H