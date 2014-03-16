#include "graphics_world.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_system.h"
#include "graphics_sprite.h"

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

void World::update()
{
    cameraStack.getTop()->update();
}

}
}
