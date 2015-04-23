#pragma once

#include "primitives.h"
#include "array.h"

namespace gengine
{
namespace physics
{

class World;

class System
{
public:
    SINGLETON(System);
    void init();
    void finalize();
    void update(const float dt);
    void createWorlds(const uint count);

    World & getWorld(const uint index);

private:
    Array<World *>
        worldTable;
};

}
}
