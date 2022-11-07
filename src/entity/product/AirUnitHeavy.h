#ifndef AIRUNITHEAVY_H
#define AIRUNITHEAVY_H

#include "AirUnit.h"

class AirUnitHeavy : public AirUnit {
   protected:
    AirUnitHeavy(const AirUnitHeavy& airUnitHeavy);

   public:
    AirUnitHeavy(std::string name, std::string type, int HP, int damage,
                 int value);

    virtual Entity* clone() override;

    ~AirUnitHeavy();
};

#endif  // AIRUNITHEAVY_H