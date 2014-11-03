#pragma once

#include "script.h"
#include "graphics_camera.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentCamera
{
public:
    ComponentCamera();

    ENTITY_COMPONENT_DECLARE();

    static SCRIPT_FUNCTION(push);
    static SCRIPT_FUNCTION(pop);
    static SCRIPT_FUNCTION(getWorldPosition);

private:
    graphics::Camera
        camera;
    uint
        worldIndex;
    bool
        itIsPushed;
};

}
}
