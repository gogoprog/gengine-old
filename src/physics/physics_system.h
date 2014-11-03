#pragma once

#include "primitives.h"
#include "array.h"
#include "Box2D/Box2D.h"

namespace gengine
{
namespace physics
{

class System
{
public:
    SINGLETON(System);
    void init();
    void finalize();
    void update(const float dt);
    void createWorlds(const uint count);

    b2World & getWorld(const uint index);

private:
    Array<b2World *>
        worldTable;
    float
        timeLeft;
};

}
}
