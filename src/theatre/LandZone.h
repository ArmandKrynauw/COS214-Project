#ifndef LANDTHEATRE_H
#define LANDTHEATRE_H

#include "Zone.h"
/**
 * This class is a ConcreteClass of the Zone Template Method Design Pattern
 * Hierarchy. This class is used to house entities of type "land" and has a
 * unique divisor of (unitCount).
 */
class LandZone : public Zone {
   private:
    /**
     * Provides functionality to get the divisor of a LandZone object
     * This function is a primitive operation of the Zone Template Method Design
     * Pattern.
     *
     * @return int Divisor of a LandZone
     */
    virtual int getDamageDivisor() override;

   public:
    /**
     * Provides functionality to create a LandZone object.
     *
     * @param name Name of zone
     */
    LandZone(std::string name);
    /**
     * Provides functionality to get the type of the zone
     *
     * @return string Type of the zone
     */
    std::string getType() override;
    /**
     * Provide functionality to destroy a LandZone object.
     */
    virtual ~LandZone();
};

#endif  // LANDTHEATRE_H