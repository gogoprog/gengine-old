#pragma once

#include "primitives.h"
#include "vector2.h"

namespace gengine
{
namespace graphics
{

struct AtlasItem
{
    AtlasItem(const Vector2 & _uvOffset, const Vector2 & _uvScale)
        :
        uvOffset(_uvOffset),
        uvScale(_uvScale)
    {
    }

    Vector2
        uvOffset,
        uvScale;
};

}
}
