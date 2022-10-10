#ifndef AIRTHEATRE_H
#define AIRTHEATRE_H

#include "Theatre.h"

class AirTheatre : public Theatre {
   private:
   public:
    AirTheatre(std::string name);
    virtual ~AirTheatre();
};

#endif  // AIRTHEATRE_H