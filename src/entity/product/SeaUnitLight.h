#ifndef SEAUNITLIGHT_H
#define SEAUNITLIGHT_H

#include "SeaUnit.h"

class SeaUnitLight : public SeaUnit {
   public:
    SeaUnitLight(std::string name, std::string type, int HP, int damage, int value);
    virtual Entity* clone() override;
    ~SeaUnitLight();
};

#endif
