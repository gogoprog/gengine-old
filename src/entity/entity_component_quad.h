#pragma once

#include "script.h"
#include "graphics_sprite.h"
#include "graphics_atlas.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentQuad
{
public:
    ComponentQuad();

    ENTITY_COMPONENT_DECLARE_OLD(ComponentQuad);

protected:
    graphics::Sprite
        sprite;
    uint
        worldIndex;
};

}
}
