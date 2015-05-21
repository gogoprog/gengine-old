#pragma once

#include "script.h"
#include "entity_macros.h"
#include "graphics_spriter_manager_item.h"
#include "graphics_spriter.h"

namespace gengine
{
namespace entity
{

class ComponentSpriter
{
public:
    ComponentSpriter();

    static SCRIPT_REGISTERER();

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(newIndex);
    static SCRIPT_FUNCTION(index);
    static SCRIPT_FUNCTION(update);

    ENTITY_COMPONENT_METHOD_DECLARE(pushAnimation);
    ENTITY_COMPONENT_METHOD_DECLARE(removeAnimations);

    static uint
        metaTableRef;
    static ENTITY_GETTER_MAP_TYPE(ComponentSpriter)
        getterMap;

protected:

    void setAnimation(const graphics::SpriterManagerItem * animation);

    Pointer<const graphics::SpriterMainlineKey>
        currentMainlineKey;
    const graphics::SpriterManagerItem
        * animation;
    Array<const graphics::SpriterManagerItem *>
        animationStack;
    graphics::SpriteGroup
        spriteGroup;
    float
        currentTime;
};

}
}
