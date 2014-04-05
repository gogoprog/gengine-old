#include "graphics_sprite.h"

namespace gengine
{
namespace graphics
{

Sprite::Sprite()
    :
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
