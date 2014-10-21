#pragma once

#include "script.h"
#include "graphics_sprite.h"
#include "graphics_atlas.h"

namespace gengine
{
namespace entity
{

class ComponentSprite
{
public:
    ComponentSprite();

    static SCRIPT_REGISTERER();

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(newIndex);
    static SCRIPT_FUNCTION(init);
    static SCRIPT_FUNCTION(insert);
    static SCRIPT_FUNCTION(update);
    static SCRIPT_FUNCTION(remove);

    static uint
        metaTableRef;

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
