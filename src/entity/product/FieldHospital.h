#ifndef FIELDHOSPITAL_H
#define FIELDHOSPITAL_H

#include "SupportCompany.h"


class FieldHospital : public  SupportCompany {
   public:
    FieldHospital(Entity* entity);
    int getDamage()  override;
    int getHP()  override;
    ~FieldHospital() override;
};

#endif  // FIELDHOSPITAL_H