#ifndef AIRTHEATRE_H
#define AIRTHEATRE_H

#include "Zone.h"

class AirZone : public Zone {
private:
    /*
     * Provides functionality to get the divisor as capacity*2
     * @return int : Divisor 
     */
    virtual int getDamageDivisor() override;

public:
    AirZone(std::string name);

    std::string getType() override;

    virtual ~AirZone();
};

#endif // AIRTHEATRE_H