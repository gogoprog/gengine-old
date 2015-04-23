#include "graphics_world.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_system.h"
#include "graphics_object.h"
#include <algorithm>

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

    std::sort(objectTable.begin(), objectTable.end(), compare);
}

void World::addObject(Object & object)
{
    objectTable.add(&object);
}

void World::removeObject(Object & object)
{
    objectTable.remove(&object);
}

void World::pushCamera(Camera & camera)
{
    cameraStack.push(&camera);
}

void World::popCamera()
{
    cameraStack.pop();
}

const Camera & World::getCurrentCamera() const
{
    return * cameraStack.getTop();
}

bool World::compare(Object *a, Object *b)
{
    return a->layer < b->layer || ( a->layer == b->layer && a > b);
}

}
}
