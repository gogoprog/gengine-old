#include "entity_component_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "script.h"

namespace gengine
{
namespace entity
{

SCRIPT_CLASS_REGISTERER(ComponentSprite)
{
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_THIS();
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(ComponentSprite, insert);
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, insert)
{
    SCRIPT_GET_SELF(ComponentSprite);

    graphics::System::getInstance().getWorld().addSprite(self.sprite);

    return 1;
}

}
}
