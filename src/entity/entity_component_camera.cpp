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
        script::fillVector2(state, self.camera.getExtent(), 3);
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, init)
{
    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, insert)
{
    SCRIPT_GET_SELF(ComponentCamera);

    graphics::System::getInstance().getWorld(0).pushCamera(self.camera);
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
        graphics::System::getInstance().getWorld(0).popCamera();
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, push)
{
    SCRIPT_GET_SELF(ComponentCamera);

    graphics::System::getInstance().getWorld(0).pushCamera(self.camera);
    self.itIsPushed = true;

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, pop)
{
    SCRIPT_GET_SELF(ComponentCamera);

    if(self.itIsPushed && & graphics::System::getInstance().getWorld(0).getCurrentCamera() == & self.camera)
    {
        graphics::System::getInstance().getWorld(0).popCamera();
        self.itIsPushed = false;
    }

    return 0;
}

SCRIPT_CLASS_FUNCTION(ComponentCamera, getWorldPosition)
{
    SCRIPT_GET_SELF(ComponentCamera);

    Vector2 pos, ratio;

    pos.x = lua_tonumber(state, 2);
    pos.y = application::getHeight() - lua_tonumber(state, 3);

    graphics::Camera & camera = self.camera;

    ratio.x = application::getWidth() / camera.getExtent().x;
    ratio.y = application::getHeight() / camera.getExtent().y;

    pos.x /= ratio.x;
    pos.y /= ratio.y;

    pos.x += camera.getPosition().x;
    pos.y += camera.getPosition().y;

    pos.x -= camera.getExtent().x * 0.5f;
    pos.y -= camera.getExtent().y * 0.5f;

    SCRIPT_PUSH_NUMBER(pos.x);
    SCRIPT_PUSH_NUMBER(pos.y);

    return 2;
}


uint
    ComponentCamera::metaTableRef;

}
}
