#include "entity_component_camera.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "application.h"
#include "entity.h"
#include "entity_macros.h"
#include "entity_entity.h"

namespace gengine
{
namespace entity
{

ComponentCamera::ComponentCamera()
    :
    Component(),
    worldIndex(0)
{
}

void ComponentCamera::init()
{
}

void ComponentCamera::insert()
{
    graphics::System::getInstance().getWorld(worldIndex).pushCamera(camera);
}

void ComponentCamera::update(const float /*dt*/)
{
    Transform & transform = entity->transform;

    camera.setPosition(transform.position);
}

void ComponentCamera::remove()
{
    graphics::System::getInstance().getWorld(worldIndex).popCamera();
}

ENTITY_COMPONENT_IMPLEMENT(ComponentCamera)
{
    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        getWorldPosition,
        {
            SCRIPT_GET_SELF(ComponentCamera);
            Vector2 result;
            Vector2 input;

            script::get(state, input, 2);
            self.camera.getWorldPosition(result, input);
            script::push(state, result);

            return 1;
        }
        );
}

ENTITY_COMPONENT_SETTERS(ComponentCamera)
{
    ENTITY_COMPONENT_SETTER_FIRST(extent)
    {
        Vector2 extent;

        script::get(state, extent, 3);

        self.camera.setExtent(extent);
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
