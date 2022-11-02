#ifndef FIELDHOSPITAL_H
#define FIELDHOSPITAL_H

#include "SupportCompany.h"


class FieldHospital : public SupportCompany {
public:
    FieldHospital(Entity *entity);
    /**
     * Provides functionality to return the entity's damage
     * @return int : damage
     */

    int getDamage() override;

    /**
     * Provides functionality to calculate the result of the entity's HP *1.25
     * @return int : HP
     */

    int getHP() override;

    virtual ~FieldHospital();
};

#endif  // FIELDHOSPITAL_H