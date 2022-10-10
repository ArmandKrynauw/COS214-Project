#ifndef THEATREFACTORY_H
#define THEATREFACTORY_H

#include <iostream> //remove later (Testing purposes)

#include "../theatre/Theatre.h"

class TheatreFactory
{ 
    private: 
    Theatre * theatre;
    public: 
    TheatreFactory();
    virtual Theatre *createTheater(std::string theatreName) = 0;
    ~TheatreFactory();
};

#endif
