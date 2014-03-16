#include "graphics_world.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_system.h"

namespace gengine
{
namespace graphics
{

World::World()
{
}

void World::init()
{
    cameraStack.push(&System::getInstance().getDefaultCamera());
}

void World::finalize()
{

}

}
}
