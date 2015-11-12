#pragma once

#include "script.h"
#include "graphics_sprite_batch.h"
#include "graphics_atlas.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentSpriteBatch
{
public:
    ComponentSpriteBatch();

    ENTITY_COMPONENT_DECLARE(ComponentSpriteBatch);

    static SCRIPT_FUNCTION(lock);
    static SCRIPT_FUNCTION(unlock);
    static SCRIPT_FUNCTION(addItem);

protected:
    graphics::SpriteBatch
        spriteBatch;
    Pointer<graphics::Atlas>
        atlas;
    uint
        worldIndex,
        size;
};

}
}
