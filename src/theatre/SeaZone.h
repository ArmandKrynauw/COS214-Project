#ifndef SEATHEATRE_H
#define SEATHEATRE_H

#include "Zone.h"

class SeaZone : public Zone {
private:
/**
     * Provides functionality to get the divisor as capacity/2
     * @return int : Divisor 
     */
    virtual int getDamageDivisor() override;

public:
    SeaZone(std::string name);

    /*
     * Provides functionality to get the type of zone
     * @return string : the type of zone
     */

    virtual std::string getType() override;

    virtual ~SeaZone();
};

#endif // SEATHEATRE_H