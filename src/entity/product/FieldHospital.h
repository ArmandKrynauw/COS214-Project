#ifndef FIELDHOSPITAL_H
#define FIELDHOSPITAL_H

#include "SupportCompany.h"


class FieldHospital : public SupportCompany {
public:
    FieldHospital(Entity *entity);

    int getDamage() override;

    /**
     * Calculates the result of the unit's HP *1.25
     * @return int : HP
     */

    int getHP() override;

    virtual ~FieldHospital();
};

#endif  // FIELDHOSPITAL_H