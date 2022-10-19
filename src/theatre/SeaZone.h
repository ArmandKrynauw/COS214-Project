#ifndef SEATHEATRE_H
#define SEATHEATRE_H

#include "Zone.h"

class SeaZone : public Zone
{
private:
        std::string type = "Sea";

public:
        SeaZone(std::string name);
        virtual ~SeaZone();
};

#endif // SEATHEATRE_H