#pragma once

#include "script.h"
#include "graphics_text.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentText
{
public:
    ComponentText();

    ENTITY_COMPONENT_DECLARE_OLD(ComponentText);

protected:
    graphics::Text
        text;
    uint
        worldIndex;
};

}
}
