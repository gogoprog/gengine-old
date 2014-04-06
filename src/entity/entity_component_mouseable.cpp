#include "entity_component_mouseable.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"
#include "input_system.h"

namespace gengine
{
namespace entity
{

ComponentMouseable::ComponentMouseable()
    :
    worldIndex(0),
    itIsHovered(false)
{
}

SCRIPT_CLASS_REGISTERER(ComponentMouseable)
{
}

SCRIPT_CLASS_FUNCTION(ComponentMouseable, create)
{
    return System::getInstance().createComponent<ComponentMouseable>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentMouseable, newIndex)
{
    SCRIPT_GET_SELF(ComponentMouseable);
    const char * key = lua_tostring(state, 2);

    if(!strcmp(key, "extent"))
    {
        script::fillVector2(state, self.extent, 3);
    }
    else if(!strcmp(key, "world"))
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    else
    {
        geLog("Unknown attribute \"" << key << "\"");
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentMouseable, init)
{
    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentMouseable, insert)
{
    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentMouseable, update)
{
    SCRIPT_GET_SELF(ComponentMouseable);

    const input::Mouse & mouse = input::System::getInstance().getMouse(0);
    const Vector2 & extent = self.extent;
    uint x,y;
    Vector2 cursor_position;
    Transform transform;

    fillTransformFromComponent(state, transform);

    const Vector2 & entity_position = transform.position;

    x = mouse.getX();
    y = mouse.getY();

    graphics::System::getInstance().getWorld(self.worldIndex).getCurrentCamera().getWorldPosition(cursor_position, Vector2(x, y));

    if(cursor_position.x > entity_position.x - extent.x * 0.5f
        && cursor_position.x < entity_position.x + extent.x * 0.5f
        && cursor_position.y > entity_position.y - extent.y * 0.5f
        && cursor_position.y < entity_position.y + extent.y * 0.5f)
    {
        if(!self.itIsHovered)
        {
            lua_getfield(state, 1, "entity");
            lua_getfield(state, -1, "onMouseEnter");
            lua_getfield(state, 1, "entity");
            lua_pcall(state, 1, 0, 0);
            lua_pop(state, 1);
            self.itIsHovered = true;
        }

        if(mouse._isJustDown(1))
        {
            lua_getfield(state, 1, "entity");
            lua_getfield(state, -1, "onMouseJustDown");
            lua_getfield(state, 1, "entity");
            lua_pcall(state, 1, 0, 0);
            lua_pop(state, 1);
        }
    }
    else
    {
        if(self.itIsHovered)
        {
            lua_getfield(state, 1, "entity");
            lua_getfield(state, -1, "onMouseExit");
            lua_getfield(state, 1, "entity");
            lua_pcall(state, 1, 0, 0);
            lua_pop(state, 1);
            self.itIsHovered = false;
        }
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentMouseable, remove)
{
    return 0;
}

uint
    ComponentMouseable::metaTableRef;

}
}
