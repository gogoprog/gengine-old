#pragma once

#include "script.h"
#include "graphics_camera.h"

namespace gengine
{
namespace entity
{

class ComponentCamera
{
public:
    ComponentCamera();

    static SCRIPT_REGISTERER();

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(newIndex);
    static SCRIPT_FUNCTION(init);
    static SCRIPT_FUNCTION(insert);
    static SCRIPT_FUNCTION(update);
    static SCRIPT_FUNCTION(remove);

    static SCRIPT_FUNCTION(push);
    static SCRIPT_FUNCTION(pop);
    static SCRIPT_FUNCTION(getWorldPosition);

    static uint
        metaTableRef;

private:
    graphics::Camera
        camera;
    bool
        itIsPushed;
};

}
}
