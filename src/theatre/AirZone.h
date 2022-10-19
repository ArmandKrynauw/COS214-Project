#ifndef AIRTHEATRE_H
#define AIRTHEATRE_H

#include "Zone.h"

class AirZone : public Zone
{
private:
    std::string type = "Air";

public:
    AirZone(std::string name,std::string type);
    virtual ~AirZone();
};

#endif // AIRTHEATRE_H