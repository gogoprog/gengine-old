#include "graphics_sprite.h"

namespace gengine
{
namespace graphics
{

Sprite::Sprite()
    :
    position(Vector2(- 1000000.0f, - 1000000.0f)),
    uvScale(Vector2::one),
    uvOffset(Vector2::zero),
    color(1.0f, 1.0f, 1.0f, 1.0f),
    rotation(0.0f),
    texture(nullptr),
    layer(0)
{

}

}
}
