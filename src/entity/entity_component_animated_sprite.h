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

    virtual void update(const float dt) override;

    ENTITY_COMPONENT_DECLARE(ComponentAnimatedSprite);

    void pushAnimation(const graphics::Animation * animation);
    void removeAnimations();

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
