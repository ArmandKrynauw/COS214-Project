#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

class Entity {
   protected:
    std::string name;
    std::string id;
    std::string type;

   public:
    Entity(std::string name, std::string type);
    virtual int getDamage() const = 0;
    std::string getName() const;
    std::string getType() const;
    std::string getId() const;
    virtual int getValue() const = 0;
    void setName(std::string name);
    virtual void print() = 0;
    virtual Entity* clone() = 0;
    virtual ~Entity();
};

#endif  // ENTITY_H