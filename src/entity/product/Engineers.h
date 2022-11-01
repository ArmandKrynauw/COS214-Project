#ifndef Engineers_H
#define Engineers_H

#include "SupportCompany.h"


class Engineers : public SupportCompany {
public:
    Engineers(Entity *entity);
    /**
     * Calculates the result of the unit's Damage *1.25 
     * @return int : HP
     */
    int getDamage() override;

    int getHP() override;

    virtual ~Engineers();
};

#endif  // Engineers_H