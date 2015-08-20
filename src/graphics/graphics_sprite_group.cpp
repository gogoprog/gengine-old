#include "graphics_sprite_group.h"

#include "graphics_renderer.h"

namespace gengine
{
namespace graphics
{

SpriteGroup::SpriteGroup()
    :
    Object(),
    activeCount(0)
{
}

SpriteGroup::~SpriteGroup()
{
    for(auto sprite_ptr : sprites)
    {
        delete sprite_ptr;
    }
}

Renderer::Type SpriteGroup::getRenderType()
{
    return Renderer::Type::SPRITE_GROUP;
}

}
}
