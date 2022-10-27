#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../utilities/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"
#include "../entity/product/Unit.h"


class Zone
{
protected:
    std::string name;
    std::string id;
    std::string type;
    std::vector<Unit*> units;

public:
    Zone(std::string name);
    int sum();
    void addUnit(Unit* unit);
    Unit* removeUnit(int index);
    std::string getType() const;
    virtual void takeDamage(int damage)=0;
    virtual std::string getType()=0;
    virtual ~Zone();
};

#endif // ZONE_H