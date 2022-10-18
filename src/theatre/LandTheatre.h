#ifndef LANDTHEATRE_H
#define LANDTHEATRE_H

#include "Theatre.h"

class LandTheatre : public Theatre
{
private:
    std : string type = "Land";

public:
    LandTheatre(std::string name);
    virtual ~LandTheatre();
};

#endif // LANDTHEATRE_H