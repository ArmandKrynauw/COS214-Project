#include "SeaTheatreFactory.h"

SeaTheatreFactory::SeaTheatreFactory() {}

Theatre *SeaTheatreFactory::createTheatre(std::string theatreName)
{
    return new SeaTheatre(theatreName);
}

SeaTheatreFactory::~SeaTheatreFactory() {}