#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../utilities/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"

class Entity;

class Zone {
protected:
    std::string name;
    std::string id;
    std::vector<Entity *> entities;


public:
    Zone(std::string name);

    int getTotalDamage();

    void addEntity(Entity *entity);

    Entity *removeEntity(std::string id);

    std::string getName() const;

    int getUnitCount() const;

    std::vector<Entity *> getEntities();

    virtual std::string getType() = 0;

    virtual ~Zone();

    // =============== Template Method ===============
    void takeDamage(int damage);

private:
    virtual int getDamageDivisor() = 0;

};

#endif // ZONE_H