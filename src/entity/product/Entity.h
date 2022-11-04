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

    virtual std::string getName() ;

    virtual int getValue() const = 0;

    virtual std::string getType() const;

    virtual std::string getId() const;

    void setName(std::string name);

    virtual Theatre *getTheatre();

    virtual bool takeDamage(int damage) = 0;

    virtual int getUnitCount() const = 0;

    virtual void setDamage(int damage);

    virtual void print() = 0;

    virtual void setTheatre(Theatre *theatre) = 0;

    virtual void clearCasualties();

    virtual Entity *clone() = 0;

    virtual nlohmann::json toJSON() const = 0;

    virtual nlohmann::json unitToJSON() const = 0;

    virtual void setHP(int hp);


    virtual ~Entity();
};

#endif  // ENTITY_H