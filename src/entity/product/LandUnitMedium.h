#ifndef LANDUNITMEDIUM_H
#define LANDUNITMEDIUM_H

#include "LandUnit.h"

class LandUnitMedium : public LandUnit {
   public:
    LandUnitMedium();
    LandUnitMedium(std::string name, std::string type, int HP, int damage, int value);
    virtual Entity* clone() override;
    ~LandUnitMedium();
};

#endif
