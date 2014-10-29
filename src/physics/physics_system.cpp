#include "physics_system.h"

#include "debug.h"

namespace gengine
{
namespace physics
{

void System::init()
{
    geDebugLog("physics::System::init()");

    createWorlds(1);
}

void System::finalize()
{
    for(b2World * world : worldTable)
    {
        delete world;
    }

    worldTable.setSize(0);
}

void System::update(const float dt)
{
    for(b2World * world : worldTable)
    {
        world->Step(dt, 8, 3);
    }
}

void System::createWorlds(const uint count)
{
    static b2Vec2 default_gravity(0.0f, -100.0f);

    int new_count = count - worldTable.getSize();

    for(int i=0; i<new_count; ++i)
    {
        b2World * world = new b2World(default_gravity);
        worldTable.add(world);
    }
}

b2World & System::getWorld(const uint index)
{
    return *worldTable[index];
}

}
}
