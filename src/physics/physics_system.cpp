#include "physics_system.h"

#include "debug.h"

#define FIXED_TIME_STEP 0.01

namespace gengine
{
namespace physics
{

void System::init()
{
    geDebugLog("physics::System::init()");

    createWorlds(1);

    timeLeft = 0.0f;
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
    timeLeft += dt;

    while(timeLeft > FIXED_TIME_STEP)
    {
        for(b2World * world : worldTable)
        {
            world->Step(FIXED_TIME_STEP, 8, 3);
        }

        timeLeft -= FIXED_TIME_STEP;
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
