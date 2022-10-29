#ifndef LANDTHEATRE_H
#define LANDTHEATRE_H

#include "Zone.h"

class LandZone : public Zone
{
private:
    virtual int getDamageDivisor() override;

public:
    LandZone(std::string name);
    std::string getType() override;
    virtual ~LandZone();
};

#endif // LANDTHEATRE_H