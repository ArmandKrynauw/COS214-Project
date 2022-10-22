#ifndef SEATHEATRE_H
#define SEATHEATRE_H

#include "Zone.h"

class SeaZone : public Zone
{
private:
        std::string type = "Sea";

public:
        SeaZone(std::string name);
        void takeDamage(int damage) override;
        std::string getType() override;
        virtual ~SeaZone();
};

#endif // SEATHEATRE_H