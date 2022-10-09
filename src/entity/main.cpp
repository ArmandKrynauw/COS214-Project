
#include "Composite.h" 
#include "entity.h"
#include "DeadState.h"



int main() {

    Composite* jan = new Composite();

    Entity* san = new Entity();

    Unit* dan = new LandUnit(5,2);

    DeadState* dead = new DeadState();

    dead->handleChange(dan);



  return 0;
}


