#include "entity_component_mouseable.h"

#include "entity_system.h"
#include "entity_entity.h"
#include "script.h"
#include "debug.h"
#include "entity.h"
#include "input_system.h"
#include "script_system.h"
#include <string.h>

using namespace gengine::math;

namespace gengine
{
namespace entity
{

ComponentMouseable::ComponentMouseable()
    :
    Component(),
    worldIndex(0),
    itIsHovered(false)
{
}

void ComponentMouseable::init()
{
}

void ComponentMouseable::insert()
{
}

void ComponentMouseable::update(const float /*dt*/)
{
    /*const input::Mouse & mouse = input::System::getInstance().getMouse(0);
    Transform & transform = entity->transform;
    const Vector2 & entity_position = transform.position;
    auto state = script::System::getInstance().getState();
    uint x,y;
    Vector2 cursor_position;

    x = mouse.getX();
    y = mouse.getY();

    //graphics::System::getInstance().getWorld(worldIndex).getCurrentCamera().getWorldPosition(cursor_position, Vector2(x, y));

    if(cursor_position.x > entity_position.x - extent.x * 0.5f
        && cursor_position.x < entity_position.x + extent.x * 0.5f
        && cursor_position.y > entity_position.y - extent.y * 0.5f
        && cursor_position.y < entity_position.y + extent.y * 0.5f)
    {
        if(!itIsHovered)
        {
            lua_getfield(state, -1, "fireEvent");
            lua_pushvalue(state, -2);
            lua_pushstring(state, "MouseEnter");
            script::System::getInstance().call(2, 0);
            itIsHovered = true;
        }

        for(uint i = input::Mouse::BUTTON_FIRST; i <= input::Mouse::BUTTON_LAST; ++i )
        {
            if(mouse.isJustDown(i))
            {
                lua_getfield(state, -1, "fireEvent");
                lua_pushvalue(state, -2);
                lua_pushstring(state, "MouseJustDown");
                lua_pushnumber(state, i);
                script::System::getInstance().call(3, 0);
            }
        }
    }
    else
    {
        if(itIsHovered)
        {
            lua_getfield(state, -1, "fireEvent");
            lua_pushvalue(state, -2);
            lua_pushstring(state, "MouseExit");
            script::System::getInstance().call(2, 0);
            itIsHovered = false;
        }
    }*/
}

void ComponentMouseable::remove()
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentMouseable)
{
}

ENTITY_COMPONENT_SETTERS(ComponentMouseable)
{
    ENTITY_COMPONENT_SETTER_FIRST(extent)
    {
        self.extent = *script::get<Vector2>(state, 3);
    }
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

}
}
