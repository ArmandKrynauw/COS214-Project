#pragma once

#include "entity.h"
#include "vector"

class Composite : public Entity{
    private:
        std::vector<Entity*> units;
    public:
        Composite(/* args */);
        ~Composite();
        void add(Entity* entity);
        int getDamage() override;
        void update();
};

