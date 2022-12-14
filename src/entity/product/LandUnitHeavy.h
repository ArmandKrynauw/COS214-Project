#ifndef LANDUNITHEAVY_H
#define LANDUNITHEAVY_H

#include "LandUnit.h"

class LandUnitHeavy : public LandUnit {
   protected:
    LandUnitHeavy(const LandUnitHeavy& landUnitHeavy);

   public:
    LandUnitHeavy();

    LandUnitHeavy(std::string name, std::string type, int HP, int damage,
                  int value);

    virtual Entity* clone() override;

    ~LandUnitHeavy();
};

#endif