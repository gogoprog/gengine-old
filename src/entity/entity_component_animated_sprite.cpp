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
        self.animation = self.animationStack[0];
        self.currentTime = 0.0f;
    }
    ENTITY_COMPONENT_SETTER_DEFAULT()
    {
        ComponentSprite::newIndex(state);
    }
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentAnimatedSprite, update)
{
    if(self.animation)
    {
        float duration = self.animation->getDuration();
        bool looping = self.animation->isLooping();

        self.currentTime += System::getInstance().getCurrentDt();

        if(!looping)
        {
            self.currentTime = std::min(duration, self.currentTime);
        }

        const graphics::AnimationFrame & frame = self.animation->getFrame(self.currentTime);

        self.sprite.setTexture(frame.atlas->getTexture());
        self.sprite.setUvOffset(frame.uvOffset);
        self.sprite.setUvScale(frame.uvScale);

        if(self.currentTime >= duration)
        {
            if(looping)
            {
                self.currentTime -= duration;
            }
            else
            {
                self.animationStack.removeLastItem();
                self.currentTime = 0.0f;

                if(self.animationStack.getSize() > 0)
                {
                    self.animation = self.animationStack.getLastItem();
                }
                else
                {
                    self.animation = nullptr;
                }
            }
        }
    }

    return ComponentSprite::update(state);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentAnimatedSprite, pushAnimation)
{
    self.animationStack.add(static_cast<const graphics::Animation *>(lua_touserdata(state, 2)));
    self.animation = self.animationStack.getLastItem();
    self.currentTime = 0.0f;
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentAnimatedSprite, removeAnimations)
{
    self.animationStack.setSize(0);
    self.animation = nullptr;
}
ENTITY_COMPONENT_END()

}
}
