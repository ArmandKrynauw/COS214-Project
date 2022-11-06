#define AIRUNITMDEIUM_H
#ifndef AIRUNITMEDIUM_H

#include "AirUnit.h"

class AirUnitMedium : public AirUnit {
protected:
    AirUnitMedium(const AirUnitMedium &airUnitMedium);

public:
    AirUnitMedium(std::string name, std::string type, int HP, int damage,
                  int value);

    virtual Entity *clone() override;

    ~AirUnitMedium();
};

#endif