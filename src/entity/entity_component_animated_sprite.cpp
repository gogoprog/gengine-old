#include "entity_component_animated_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"

namespace gengine
{
namespace entity
{

ComponentAnimatedSprite::ComponentAnimatedSprite()
    :
    ComponentSprite()
{
}

SCRIPT_CLASS_REGISTERER(ComponentAnimatedSprite)
{
}

SCRIPT_CLASS_FUNCTION(ComponentAnimatedSprite, create)
{
    return System::getInstance().createComponent<ComponentAnimatedSprite>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentAnimatedSprite, newIndex)
{
    SCRIPT_GET_SELF(ComponentAnimatedSprite);
    const char * key = lua_tostring(state, 2);

    ComponentSprite::newIndex(state);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentAnimatedSprite, update)
{
    return ComponentSprite::update(state);
}

uint
    ComponentAnimatedSprite::metaTableRef;

}
}
