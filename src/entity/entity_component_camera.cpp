#include "entity_component_camera.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "application.h"
#include "entity.h"

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

SCRIPT_CLASS_REGISTERER(ComponentCamera)
{
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(ComponentCamera, getWorldPosition);
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, create)
{
    return System::getInstance().createComponent<ComponentCamera>(state);
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, newIndex)
{
    SCRIPT_GET_SELF(ComponentCamera);
    const char * key = lua_tostring(state, 2);

    if(!strcmp(key,"extent"))
    {
        Vector2::fill(state, self.camera.getExtent(), 3);
    }
    else if(!strcmp(key,"world"))
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    else
    {
        geLog("Unknown attribute \"" << key << "\"");
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, init)
{
    (void)state;
    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, insert)
{
    SCRIPT_GET_SELF(ComponentCamera);

    graphics::System::getInstance().getWorld(self.worldIndex).pushCamera(self.camera);
    self.itIsPushed = true;

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, update)
{
    SCRIPT_GET_SELF(ComponentCamera);

    graphics::Camera & camera = self.camera;

    Transform transform;
    fillTransformFromComponent(state, transform);

    camera.setPosition(transform.position);

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, remove)
{
    SCRIPT_GET_SELF(ComponentCamera);

    if(self.itIsPushed)
    {
        graphics::System::getInstance().getWorld(self.worldIndex).popCamera();
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, push)
{
    SCRIPT_GET_SELF(ComponentCamera);

    graphics::System::getInstance().getWorld(self.worldIndex).pushCamera(self.camera);
    self.itIsPushed = true;

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, pop)
{
    SCRIPT_GET_SELF(ComponentCamera);

    if(self.itIsPushed && & graphics::System::getInstance().getWorld(self.worldIndex).getCurrentCamera() == & self.camera)
    {
        graphics::System::getInstance().getWorld(self.worldIndex).popCamera();
        self.itIsPushed = false;
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, getWorldPosition)
{
    SCRIPT_GET_SELF(ComponentCamera);

    Vector2 result;

    self.camera.getWorldPosition(result, Vector2(lua_tonumber(state, 2), lua_tonumber(state, 3)));

    SCRIPT_PUSH_NUMBER(result.x);
    SCRIPT_PUSH_NUMBER(result.y);

    return 2;
}

uint
    ComponentCamera::metaTableRef;

}
}
