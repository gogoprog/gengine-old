#pragma once

#include "primitives.h"
#include "vector2.h"

namespace gengine
{
namespace graphics
{

class Texture;

struct AnimationFrame
{
    const Texture
        * texture;
    Vector2
        uvOffset,
        uvScale;
};

}
}
