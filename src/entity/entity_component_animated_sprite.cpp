#include "entity_component_animated_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "graphics_animation.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"
#include <algorithm>

namespace gengine
{
namespace entity
{

ComponentAnimatedSprite::ComponentAnimatedSprite()
    :
    ComponentSprite(),
    animation(nullptr),
    currentTime(0.0f)
{
}

void ComponentAnimatedSprite::update(const float dt)
{
    if(animation)
    {
        float duration = animation->getDuration();
        bool looping = animation->isLooping();

        currentTime += dt;

        if(!looping)
        {
            currentTime = std::min(duration, currentTime);
        }

        const graphics::AnimationFrame & frame = animation->getFrame(currentTime);

        sprite.setTexture(frame.atlas->getTexture());
        sprite.setUvOffset(frame.uvOffset);
        sprite.setUvScale(frame.uvScale);

        if(currentTime >= duration)
        {
            if(looping)
            {
                currentTime -= duration;
            }
            else
            {
                animationStack.removeLastItem();

                if(animationStack.getSize() > 0)
                {
                    setAnimation(animationStack.getLastItem());
                }
                else
                {
                    animation = nullptr;
                }
            }
        }
    }

    ComponentSprite::update(dt);
}

ENTITY_COMPONENT_IMPLEMENT(ComponentAnimatedSprite)
{
    ENTITY_COMPONENT_PUSH_FUNCTION(pushAnimation);
    ENTITY_COMPONENT_PUSH_FUNCTION(removeAnimations);
}

ENTITY_COMPONENT_SETTERS(ComponentAnimatedSprite)
{
    ENTITY_COMPONENT_SETTER_FIRST(animation)
    {
        self.animationStack.setSize(1);
        self.animationStack[0] = static_cast<const graphics::Animation *>(lua_touserdata(state, 3));
        self.setAnimation(self.animationStack.getLastItem());
    }
    ENTITY_COMPONENT_SETTER_DEFAULT()
    {
        ComponentSprite::_newIndex(state);
    }
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentAnimatedSprite, pushAnimation)
{
    self.animationStack.add(static_cast<const graphics::Animation *>(lua_touserdata(state, 2)));
    self.setAnimation(self.animationStack.getLastItem());
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentAnimatedSprite, removeAnimations)
{
    self.animationStack.setSize(0);
    self.animation = nullptr;
}
ENTITY_COMPONENT_END()

void ComponentAnimatedSprite::setAnimation(const graphics::Animation * _animation)
{
    animation = _animation;
    currentTime = 0.0f;

    if(!extentHasBeenSet)
    {
        animation->getFrame(0.0f).atlas->getDefaultExtent(sprite.getExtent(), 0);
    }
}

}
}
