#include "entity_component_mouseable.h"

#include "core.h"
#include "application.h"
#include "entity_system.h"
#include "entity_entity.h"
#include "script.h"
#include "debug.h"
#include "entity.h"
#include "input_system.h"
#include "script_system.h"
#include <string.h>
#include <Urho3D/Graphics/Camera.h>

using namespace gengine::math;

namespace gengine
{
namespace entity
{

ComponentMouseable::ComponentMouseable()
    :
    Component(),
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
    auto & input_system = input::System::getInstance();
    auto & camera = * core::getRenderer().GetViewport(0)->GetCamera();
    auto mouse_position = input_system.getMousePosition();
    auto state = script::System::getInstance().getState();

    mouse_position /= math::Vector2(application::getWidth(), application::getHeight());

    auto mouse_world_position = camera.ScreenToWorldPoint(Vector3(mouse_position.x_, mouse_position.y_, 0));
    auto entity_position = entity->getPosition2D();

    if(mouse_world_position.x_ > entity_position.x_ - extent.x_ * 0.5f
        && mouse_world_position.x_ < entity_position.x_ + extent.x_ * 0.5f
        && mouse_world_position.y_ > entity_position.y_ - extent.y_ * 0.5f
        && mouse_world_position.y_ < entity_position.y_ + extent.y_ * 0.5f)
    {
        if(!itIsHovered)
        {
            lua_getfield(state, -1, "fireEvent");
            lua_pushvalue(state, -2);
            lua_pushstring(state, "MouseEnter");
            script::System::getInstance().call(2, 0);
            itIsHovered = true;
        }

        for(uint i = 0; i <= 3; ++i )
        {
            if(input_system.isMouseButtonJustDown(i))
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
    }
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
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

}
}
