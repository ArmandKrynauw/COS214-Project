#ifndef AIRTHEATRE_H
#define AIRTHEATRE_H

#include "Zone.h"
/**
 * This class is a ConcreteClass of the Zone Template Method Design Pattern. This class is used to house entities
 * of type "air" and has a unique divisor of (unitCount * 2).
 */
class AirZone : public Zone {
    private:
        /**
         * Provides functionality to get the divisor of a AirZone object
         * This function is a primitive operation of the Zone Template Method Design Pattern.
         * 
         * @return int Divisor of a AirZone
         */
        virtual int getDamageDivisor() override;
    public:
        /**
         * Provides functionality to create an AirZone object.
         * 
         * @param name Name of zone
         */
        AirZone(std::string name);
        /**
         * Provides functionality to get the type of the zone
         * 
         * @return string Type of the zone
         */
        std::string getType() override;
        /**
         * Provide functionality to destroy a AirZone object.
         */
        virtual ~AirZone();
};

#endif // AIRTHEATRE_H