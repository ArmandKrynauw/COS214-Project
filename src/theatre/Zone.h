#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../exception/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"
#include "../entity/product/Unit.h"


class Zone
{
protected:
    std::string name;
    std::string id;
    std::vector<Unit*> units;
public:
    Zone(std::string name);
    int sum();
    void addUnit(Unit* unit);
    Unit* removeUnit(int index);
    virtual void takeDamage(int damage)=0;
    virtual std::string getType()=0;
    virtual ~Zone() = 0;
};

#endif // ZONE_H