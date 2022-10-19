#define AIRUNITMDEIUM_H
#ifndef AIRUNITMEDIUM_H

#include "AirUnit.h"

class AirUnitMedium : public AirUnit{
    public:
        AirUnitMedium(std::string name, std::string type, int HP, int damage);
        virtual Entity* clone() override;
        ~AirUnitMedium();
};

#endif