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

    ENTITY_COMPONENT_METHOD_DECLARE(push);
    ENTITY_COMPONENT_METHOD_DECLARE(pop);
    ENTITY_COMPONENT_METHOD_DECLARE(getWorldPosition);

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
