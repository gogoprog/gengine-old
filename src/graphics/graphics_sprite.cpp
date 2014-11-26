#include "graphics_sprite.h"

#include "graphics_renderer.h"

namespace gengine
{
namespace graphics
{

Sprite::Sprite()
    :
    Object(),
    uvScale(Vector2::one),
    uvOffset(Vector2::zero),
    texture()
{
}

Renderer::Type Sprite::getRenderType()
{
    return Renderer::Type::SPRITE;
}


}
}
