#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "entity.h"
#include "vector"

class Composite : public Entity{
    private:
        std::vector<Entity*> units;
    public:
        Composite(/* args */);
        ~Composite();
        void add(Entity* entity);
        void Delete(int a);
        std::string print() override;
        int getDamage() override;
        void update();
};


#endif // COMPOSITE_H