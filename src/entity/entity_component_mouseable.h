#pragma once

#include "script.h"
#include "primitives.h"

namespace gengine
{
namespace entity
{

class ComponentMouseable
{
public:
    ComponentMouseable();

    static SCRIPT_REGISTERER();

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(newIndex);
    static SCRIPT_FUNCTION(init);
    static SCRIPT_FUNCTION(insert);
    static SCRIPT_FUNCTION(update);
    static SCRIPT_FUNCTION(remove);

    static uint
        metaTableRef;

private:
    Vector2
        extent;
    uint
        worldIndex;
    bool
        itIsHovered;
};

}
}
