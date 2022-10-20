#ifndef AIRUNITLIGHT_H
#define AIRUNITLIGHT_H

#include "AirUnit.h"

class AirUnitLight : public AirUnit {
   public:
    AirUnitLight(std::string name, std::string type, int HP, int damage);
    virtual Entity* clone() override;
    ~AirUnitLight();
};

#endif  // AIRUNITLIGHT_H