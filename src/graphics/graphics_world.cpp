#include "graphics_world.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_system.h"
#include "graphics_sprite.h"
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

    std::sort(spriteTable.begin(), spriteTable.end(), compare);
}

void World::addSprite(Sprite & sprite)
{
    spriteTable.add(&sprite);
}

void World::removeSprite(Sprite & sprite)
{
    spriteTable.remove(&sprite);
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

bool World::compare(Sprite *a, Sprite *b)
{
    return a->layer < b->layer || ( a->layer == b->layer && a > b);
}

}
}
