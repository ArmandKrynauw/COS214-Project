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
    virtual int getHP() const = 0;
    virtual int getDamage() const = 0;
    std::string getName() const;
    std::string getType() const;
    void setName(std::string name);
    // virtual std::string print() = 0;
    virtual Entity* clone() = 0;
    virtual ~Entity();
};

#endif  // ENTITY_H