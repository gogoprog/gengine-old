#include "navigation_system.h"

#include "debug.h"
#include "navigation_world.h"

namespace gengine
{
namespace navigation
{

void System::init()
{
    geDebugLog("navigation::System::init()");
}

void System::finalize()
{
    for(World * world : worldTable)
    {
        delete world;
    }

    worldTable.setSize(0);
}

void System::update(const float dt)
{
    for(World * world : worldTable)
    {
        world->update(dt);
    }
}

void System::createWorlds(const uint count)
{
    int new_count = count - worldTable.getSize();

    for(int i=0; i<new_count; ++i)
    {
        World * world = new World();
        worldTable.add(world);
    }
}

World & System::getWorld(const uint index)
{
    return *worldTable[index];
}

}
}
