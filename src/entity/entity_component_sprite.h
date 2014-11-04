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

    ENTITY_COMPONENT_DECLARE();

protected:
    graphics::Sprite
        sprite;
    graphics::Atlas
        * atlas;
    uint
        worldIndex,
        atlasItem;
};

}
}
