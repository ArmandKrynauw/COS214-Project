#ifndef SEATHEATRE_H
#define SEATHEATRE_H

#include "Theatre.h"

class SeaTheatre : public Theatre
{
private:
        std::string type = "Sea";

public:
        SeaTheatre(std::string name);
        virtual ~SeaTheatre();
};

#endif // SEATHEATRE_H