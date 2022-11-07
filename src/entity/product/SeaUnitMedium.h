#ifndef SEAUNITMEDIUM_H
#define SEAUNITMEDIUM_H

#include "SeaUnit.h"

class SeaUnitMedium : public SeaUnit {
   protected:
    SeaUnitMedium(const SeaUnitMedium& seaUnitMedium);

   public:
    SeaUnitMedium(std::string name, std::string type, int HP, int damage,
                  int value);

    virtual Entity* clone() override;

    ~SeaUnitMedium();
};

#endif
