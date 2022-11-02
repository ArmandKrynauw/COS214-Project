#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

#include "../../theatre/Theatre.h"
#include "../../utilities/json.hpp"

class Entity {
protected:
    std::string name;
    std::string id;
    std::string type;

public:
    Entity();

    Entity(std::string name, std::string type);

    virtual int getDamage() = 0;

    virtual int getHP() = 0;

    std::string getName() const;

    std::string getType() const;

    std::string getId() const;

    virtual int getValue() const = 0;

    void setName(std::string name);

    virtual bool takeDamage(int damage) = 0;

    virtual int getUnitCount() const = 0;

    virtual void print() = 0;

    virtual void setTheatre(Theatre *theatre) = 0;

    virtual Entity *clone() = 0;

    virtual nlohmann::json toJSON() const = 0;

    virtual nlohmann::json unitToJSON() const = 0;

    virtual ~Entity();
};

#endif  // ENTITY_H