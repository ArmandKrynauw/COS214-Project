#ifndef AIRTHEATRE_H
#define AIRTHEATRE_H

#include "Theatre.h"

class AirTheatre : public Theatre
{
private:
    std::string type = "Air";

public:
    AirTheatre(std::string name);
    virtual ~AirTheatre();
};

#endif // AIRTHEATRE_H