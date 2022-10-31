#ifndef Engineers_H
#define Engineers_H

#include "SupportCompany.h"


class Engineers : public  SupportCompany {
   public:
    Engineers(Entity* entity);
    int getDamage()  override;
    int getHP()  override;
    ~Engineers() override;
};

#endif  // Engineers_H