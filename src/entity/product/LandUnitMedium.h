#ifndef LANDUNITMEDIUM_H
#define LANDUNITMEDIUM_H

#include "LandUnit.h"

class LandUnitMedium : public LandUnit {
protected:
    LandUnitMedium(const LandUnitMedium &landUnitMedium);
public:
    LandUnitMedium();

    LandUnitMedium(std::string name, std::string type, int HP, int damage,
                   int value);

    virtual Entity *clone() override;

    ~LandUnitMedium();
};

#endif
