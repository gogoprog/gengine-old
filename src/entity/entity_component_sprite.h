#pragma once

#include "script.h"
#include "graphics_sprite.h"

namespace gengine
{
namespace entity
{

class ComponentSprite
{
public:
    ComponentSprite() = default;

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(newIndex);
    static SCRIPT_FUNCTION(init);
    static SCRIPT_FUNCTION(insert);
    static SCRIPT_FUNCTION(update);
    static SCRIPT_FUNCTION(remove);

    static uint metaTableRef;

private:
    graphics::Sprite
        sprite;
};

}
}
