#ifndef SEATHEATRE_H
#define SEATHEATRE_H

#include "Zone.h"
/**
 * This class is a ConcreteClass of the Zone Template Method Design Pattern. This class is used to house entities
 * of type "sea" and has a unique divisor of (unitCount / 2).
 */
class SeaZone : public Zone {
    private:
        /**
         * Provides functionality to get the divisor of a SeaZone object
         * This function is a primitive operation of the Zone Template Method Design Pattern.
         * 
         * @return int Divisor of a SeaZone
         */
        virtual int getDamageDivisor() override;
    public:
        /**
         * Provides functionality to create a SeaZone object.
         * 
         * @param name Name of zone
         */
        SeaZone(std::string name);
        /**
         * Provides functionality to get the type of the zone
         * 
         * @return string Type of the zone
         */
        virtual std::string getType() override;
        /**
         * Provide functionality to destroy a SeaZone object.
         */
        virtual ~SeaZone();
};

#endif // SEATHEATRE_H