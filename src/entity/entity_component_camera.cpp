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

namespace gengine
{
namespace entity
{

ComponentCamera::ComponentCamera()
    :
    worldIndex(0),
    itIsPushed(false)
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentCamera)
{
    ENTITY_COMPONENT_PUSH_FUNCTION(getWorldPosition);
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

ENTITY_COMPONENT_METHOD(ComponentCamera, init)
{
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentCamera, insert)
{
    graphics::System::getInstance().getWorld(self.worldIndex).pushCamera(self.camera);
    self.itIsPushed = true;
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentCamera, update)
{
    graphics::Camera & camera = self.camera;

    Transform transform;
    fillTransformFromComponent(state, transform);

    camera.setPosition(transform.position);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentCamera, remove)
{
    if(self.itIsPushed)
    {
        graphics::System::getInstance().getWorld(self.worldIndex).popCamera();
    }
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentCamera, push)
{
    graphics::System::getInstance().getWorld(self.worldIndex).pushCamera(self.camera);
    self.itIsPushed = true;
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentCamera, pop)
{
    if(self.itIsPushed && & graphics::System::getInstance().getWorld(self.worldIndex).getCurrentCamera() == & self.camera)
    {
        graphics::System::getInstance().getWorld(self.worldIndex).popCamera();
        self.itIsPushed = false;
    }
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentCamera, getWorldPosition)
{
    Vector2 result, input;

    script::get(state, input, 2);

    self.camera.getWorldPosition(result, input);

    script::push(state, result);

    return 1;
}
ENTITY_COMPONENT_END()

}
}
