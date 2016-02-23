#include "entity_component_animated_sprite.h"

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
    currentTime(0.0f)
{
}

void ComponentAnimatedSprite::update(const float dt)
{
    /*if(animation)
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

    ComponentSprite::update(dt);*/
}

/*
void ComponentAnimatedSprite::pushAnimation(const graphics::Animation * animation)
{
    animationStack.add(animation);
    setAnimation(animationStack.getLastItem());
}*/

void ComponentAnimatedSprite::removeAnimations()
{
    /*animationStack.setSize(0);
    animation = nullptr;*/
}

ENTITY_COMPONENT_IMPLEMENT(ComponentAnimatedSprite)
{
    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        pushAnimation,
        {
            SCRIPT_GET_SELF(ComponentAnimatedSprite);
            //self.pushAnimation(static_cast<const graphics::Animation*>(lua_touserdata(state, 2)));
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        removeAnimations,
        {
            SCRIPT_GET_SELF(ComponentAnimatedSprite);
            //self.removeAnimations();
            return 0;
        }
        );
}

ENTITY_COMPONENT_SETTERS(ComponentAnimatedSprite)
{
    ENTITY_COMPONENT_SETTER_FIRST(animation)
    {
        /*self.animationStack.setSize(1);
        self.animationStack[0] = static_cast<const graphics::Animation *>(lua_touserdata(state, 3));
        self.setAnimation(self.animationStack.getLastItem());*/
    }
    ENTITY_COMPONENT_SETTER_DEFAULT()
    {
        ComponentSprite::_newIndex(state);
    }
}
ENTITY_COMPONENT_END()
/*
void ComponentAnimatedSprite::setAnimation(const graphics::Animation * _animation)
{
    animation = _animation;
    currentTime = 0.0f;

    if(!extentHasBeenSet)
    {
        animation->getFrame(0.0f).atlas->getDefaultExtent(sprite.getExtent(), 0);
    }
}
*/
}
}
