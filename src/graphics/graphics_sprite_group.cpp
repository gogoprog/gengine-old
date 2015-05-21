#include "graphics_sprite_group.h"

#include "graphics_renderer.h"

namespace gengine
{
namespace graphics
{

SpriteGroup::SpriteGroup()
    :
    Object()
{
}

Renderer::Type SpriteGroup::getRenderType()
{
    return Renderer::Type::SPRITE_GROUP;
}

}
}
