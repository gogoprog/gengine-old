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

    SCRIPT_REGISTERER();

    //static SCRIPT_FUNCTION(init);
    static SCRIPT_FUNCTION(insert);
    //static SCRIPT_FUNCTION(update);
    //static SCRIPT_FUNCTION(remove);

private:
    graphics::Sprite
        sprite;
};

}
}
