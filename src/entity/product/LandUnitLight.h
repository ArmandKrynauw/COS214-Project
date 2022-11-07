#ifndef LANDUNITLIGHT_H
#define LANDUNITLIGHT_H

#include "LandUnit.h"

class LandUnitLight : public LandUnit {
   protected:
    LandUnitLight(const LandUnitLight& landUnitLight);

   public:
    LandUnitLight();

    LandUnitLight(std::string name, std::string type, int HP, int damage,
                  int value);

    virtual Entity* clone() override;

    ~LandUnitLight();
};

#endif