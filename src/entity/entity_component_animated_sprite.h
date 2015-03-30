#pragma once

#include "entity_component_sprite.h"
#include "script.h"
#include "graphics_animation.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentAnimatedSprite : public ComponentSprite
{
public:
    ComponentAnimatedSprite();

    static SCRIPT_REGISTERER();

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(newIndex);
    static SCRIPT_FUNCTION(update);

    ENTITY_COMPONENT_METHOD_DECLARE(pushAnimation);
    ENTITY_COMPONENT_METHOD_DECLARE(removeAnimations);

    static uint
        metaTableRef;

protected:

    void setAnimation(const graphics::Animation * animation);

    const graphics::Animation
        * animation;
    Array<const graphics::Animation *>
        animationStack;
    float
        currentTime;
};

}
}
