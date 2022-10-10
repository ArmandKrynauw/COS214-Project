#ifndef AIRTHEATREFACTORY_H
#define AIRTHEATREFACTORY_H

#include "TheatreFactory.h"
#include "../theatre/AirTheatre.h"

class AirTheatreFactory : public TheatreFactory {
    private:
    public:
        AirTheatreFactory();
        Theatre* createTheatre(std::string theatreName);
        ~AirTheatreFactory();
};

#endif