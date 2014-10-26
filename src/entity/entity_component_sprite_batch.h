#pragma once

#include "script.h"
#include "graphics_sprite_batch.h"

namespace gengine
{
namespace entity
{

class ComponentSpriteBatch
{
public:
    ComponentSpriteBatch();

    static SCRIPT_REGISTERER();

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(newIndex);
    static SCRIPT_FUNCTION(init);
    static SCRIPT_FUNCTION(insert);
    static SCRIPT_FUNCTION(update);
    static SCRIPT_FUNCTION(remove);

    static SCRIPT_FUNCTION(lock);
    static SCRIPT_FUNCTION(unlock);
    static SCRIPT_FUNCTION(addItem);

    static uint
        metaTableRef;

protected:
    graphics::SpriteBatch
        spriteBatch;
    uint
        worldIndex;
};

}
}
