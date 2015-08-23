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

    ENTITY_COMPONENT_METHOD_DECLARE(pushAnimation);
    ENTITY_COMPONENT_METHOD_DECLARE(removeAnimations);

    ENTITY_COMPONENT_DECLARE(ComponentSpriter);

protected:

    void setAnimation(const graphics::SpriterManagerItem * animation, const bool reset_time);

    Pointer<const graphics::SpriterMainlineKey>
        currentMainlineKey;
    Pointer<const graphics::SpriterCharacterMap>
        characterMap;
    Pointer<const graphics::SpriterEntity>
        lastSpriterEntity;
    const graphics::SpriterManagerItem
        * animation;
    Array<const graphics::SpriterManagerItem *>
        animationStack;
    graphics::SpriteGroup
        spriteGroup;
    float
        currentTime,
        timeFactor;
    uint
        worldIndex;
};

}
}
