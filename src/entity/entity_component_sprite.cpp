#include "entity_component_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"

namespace gengine
{
namespace entity
{

SCRIPT_CLASS_FUNCTION(ComponentSprite, create)
{
    return System::getInstance().createComponent<ComponentSprite>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, insert)
{
    SCRIPT_GET_SELF(ComponentSprite);

    graphics::System::getInstance().getWorld(0).addSprite(self.sprite);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, update)
{
    SCRIPT_GET_SELF(ComponentSprite);

    (void)self;


    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, remove)
{
    SCRIPT_GET_SELF(ComponentSprite);

    (void)self;
    // :TODO:
    //graphics::System::getInstance().getWorld(0).removeSprite(self.sprite);

    return 0;
}

uint ComponentSprite::metaTableRef;

}
}
