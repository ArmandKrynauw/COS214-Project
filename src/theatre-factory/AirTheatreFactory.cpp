#include "AirTheatreFactory.h"

AirTheatreFactory::AirTheatreFactory() {}

Theatre *AirTheatreFactory::createTheatre(std::string theatreName)
{
    return new AirTheatre(theatreName);
}

AirTheatreFactory::~AirTheatreFactory() {}