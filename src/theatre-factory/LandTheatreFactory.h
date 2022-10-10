#ifndef LANDTHEATREFACTORY_H
#define LANDTHEATREFACTORY_H

#include "TheatreFactory.h"
#include "../theatre/LandTheatre.h"

class LandTheatreFactory : public TheatreFactory {
    private:
    public:
        LandTheatreFactory();
        Theatre* createTheatre(std::string theatreName);
        ~LandTheatreFactory();
};

#endif 