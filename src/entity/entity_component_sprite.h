#pragma once

#include "script.h"
#include "graphics_sprite.h"
#include "graphics_atlas.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentSprite
{
public:
    ComponentSprite();

    ENTITY_COMPONENT_DECLARE(ComponentSprite);

protected:
    graphics::Sprite
        sprite;
    graphics::Atlas
        * atlas;
    math::Vector2
        extent;
    uint
        worldIndex,
        atlasItem;
    bool
        extentHasBeenSet;
};

}
}
