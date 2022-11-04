#ifndef FIELDHOSPITAL_H
#define FIELDHOSPITAL_H

#include "SupportCompany.h"

class FieldHospital : public SupportCompany {
public:
    FieldHospital(Entity* entity);

    bool takeDamage(int damage) override;

    /**
     * Provides functionality to return the entity's name abbreviated with -FH
     * @return string : result of entity's getName() + -FH
     */
    std::string getName() const override;

    virtual ~FieldHospital();

};

#endif  // FIELDHOSPITAL_H