#ifndef LANDUNITHEAVY_H
#define LANDUNITHEAVY_H

#include "LandUnit.h"

class LandUnitHeavy : public LandUnit{
    public:
        LandUnitHeavy();
        LandUnitHeavy(std::string name, std::string type, int HP, int damage);
        virtual Entity* clone() override;
        ~LandUnitHeavy();
};

#endif