#ifndef LANDTHEATRE_H
#define LANDTHEATRE_H

#include "Zone.h"

class LandZone : public Zone
{
private:
    std:: string type = "Land";

public:
    LandZone(std::string name);
    void takeDamage(int damage) override;
    std::string getType() override;
    virtual ~LandZone();
};

#endif // LANDTHEATRE_H