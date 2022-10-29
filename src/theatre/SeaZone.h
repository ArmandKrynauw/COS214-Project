#ifndef SEATHEATRE_H
#define SEATHEATRE_H

#include "Zone.h"

class SeaZone : public Zone
{
private:
        virtual int getDamageDivisor() override;

public:
        SeaZone(std::string name);
        virtual std::string getType() override;
        virtual ~SeaZone();
};

#endif // SEATHEATRE_H