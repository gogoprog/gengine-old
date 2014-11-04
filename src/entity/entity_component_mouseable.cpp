#include "entity_component_mouseable.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"
#include "input_system.h"
#include "script_system.h"

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

ENTITY_COMPONENT_SETTERS(ComponentMouseable)
{
    ENTITY_COMPONENT_SETTER_FIRST(extent)
    {
        Vector2::fill(state, self.extent, 3);
    }
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

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
            script::System::getInstance().call(1, 0);
            lua_pop(state, 1);
            self.itIsHovered = true;
        }

        for(uint i = input::Mouse::BUTTON_FIRST; i <= input::Mouse::BUTTON_LAST; ++i )
        {
            if(mouse._isJustDown(i))
            {
                lua_getfield(state, 1, "entity");
                lua_getfield(state, -1, "onMouseJustDown");
                lua_getfield(state, 1, "entity");
                lua_pushnumber(state, i);
                script::System::getInstance().call(2, 0);
                lua_pop(state, 1);
            }
        }
    }
    else
    {
        if(self.itIsHovered)
        {
            lua_getfield(state, 1, "entity");
            lua_getfield(state, -1, "onMouseExit");
            lua_getfield(state, 1, "entity");
            script::System::getInstance().call(1, 0);
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
