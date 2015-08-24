#pragma once

#include "primitives.h"
#include "vector2.h"

namespace gengine
{
namespace graphics
{

struct AtlasItem
{
    AtlasItem(const math::Vector2 & _uvOffset, const math::Vector2 & _uvScale)
        :
        uvOffset(_uvOffset),
        uvScale(_uvScale)
    {
    }

    math::Vector2
        uvOffset,
        uvScale;
};

}
}
