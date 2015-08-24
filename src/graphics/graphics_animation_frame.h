#pragma once

#include "primitives.h"
#include "vector2.h"
#include "graphics_atlas.h"

namespace gengine
{
namespace graphics
{

struct AnimationFrame
{
    AnimationFrame(const Atlas * _atlas, const uint item_index)
        :
        atlas(_atlas),
        uvOffset(atlas->getItem(item_index).uvOffset),
        uvScale(atlas->getItem(item_index).uvScale)
    {
    }

    const Atlas
        * atlas;
    const math::Vector2
        & uvOffset,
        & uvScale;
};

}
}
