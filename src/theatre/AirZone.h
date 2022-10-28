#ifndef AIRTHEATRE_H
#define AIRTHEATRE_H

#include "Zone.h"

class AirZone : public Zone{
    private:

    public:
        AirZone(std::string name);
        void takeDamage(int damage) override;
        std::string getType() override;
        virtual ~AirZone();
};

#endif // AIRTHEATRE_H