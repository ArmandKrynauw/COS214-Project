#ifndef SEATHEATREFACTORY_H
#define SEATHEATREFACTORY_H

#include "TheatreFactory.h"
#include "../product/SeaTheatre.h"

class SeaTheatreFactory : public TheatreFactory {
    private:
    public:
        SeaTheatreFactory();
        Theatre* createTheatre(std::string theatreName);
        ~SeaTheatreFactory();
};

#endif
