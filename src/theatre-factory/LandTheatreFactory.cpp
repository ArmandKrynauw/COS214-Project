#include "LandTheatreFactory.h"

LandTheatreFactory::LandTheatreFactory() {}

Theatre *LandTheatreFactory::createTheatre(std::string theatreName)
{
    return new LandTheatre(theatreName);
}

LandTheatreFactory::~LandTheatreFactory() {}