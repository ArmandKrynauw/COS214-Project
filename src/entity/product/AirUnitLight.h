#ifndef AIRUNITLIGHT_H
#define AIRUNITLIGHT_H

#include "AirUnit.h"

class AirUnitLight : public AirUnit {
   protected:
    AirUnitLight(const AirUnitLight& airUnitLight);

   public:
    AirUnitLight(std::string name, std::string type, int HP, int damage,
                 int value);

    virtual Entity* clone() override;

    ~AirUnitLight();
};

#endif  // AIRUNITLIGHT_H