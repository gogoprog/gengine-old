#include "entity_component_spriter.h"

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

ComponentSpriter::ComponentSpriter()
    :
    animation(nullptr),
    currentTime(0.0f),
    worldIndex(0)
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentSpriter)
{
    ENTITY_COMPONENT_PUSH_FUNCTION(pushAnimation);
    ENTITY_COMPONENT_PUSH_FUNCTION(removeAnimations);
}

ENTITY_COMPONENT_SETTERS(ComponentSpriter)
{
    ENTITY_COMPONENT_SETTER_FIRST(animation)
    {
        self.animationStack.setSize(1);
        self.animationStack[0] = static_cast<const graphics::SpriterManagerItem *>(lua_touserdata(state, 3));
        self.setAnimation(self.animationStack.getLastItem(), true);
    }
    ENTITY_COMPONENT_SETTER(layer)
    {
        self.spriteGroup.setLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(characterMap)
    {
        if(self.lastSpriterEntity)
        {
            self.characterMap = self.lastSpriterEntity->getCharacterMap(lua_tostring(state,3));
        }
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriter, init)
{
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriter, insert)
{
    graphics::System::getInstance().getWorld(self.worldIndex).addObject(self.spriteGroup);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriter, update)
{
    if(self.animation)
    {
        float duration = self.animation->getDuration();
        bool looping = self.animation->isLooping();

        self.currentTime += System::getInstance().getCurrentDt();

        if(self.currentTime > duration)
        {
            while(self.currentTime > duration)
            {
                self.currentTime -= duration;
            }

            if(!looping)
            {
                self.animationStack.removeLastItem();

                if(self.animationStack.getSize() > 0)
                {
                    self.setAnimation(self.animationStack.getLastItem(), false);
                }
                else
                {
                    self.currentTime = duration;
                }
            }
        }

        Pointer<const graphics::SpriterMainlineKey> mlk = & self.animation->getAnimation().getMainlineKey(self.currentTime);

        if(self.currentMainlineKey != mlk)
        {
            self.currentMainlineKey = mlk;
            self.animation->fill(self.spriteGroup, *mlk, self.characterMap);
        }

        self.animation->update(self.spriteGroup, *mlk, self.currentTime, self.characterMap);

        if(!looping && self.currentTime == duration && !self.animationStack.getSize())
        {
            self.animation = nullptr;
        }

        graphics::SpriteGroup & spriteGroup = self.spriteGroup;

        Transform transform;
        fillTransformFromComponent(state, transform);

        spriteGroup.setPosition(transform.position);
        spriteGroup.setRotation(transform.rotation);
    }
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriter, remove)
{
    graphics::System::getInstance().getWorld(self.worldIndex).removeObject(self.spriteGroup);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriter, pushAnimation)
{
    self.animationStack.add(static_cast<const graphics::SpriterManagerItem *>(lua_touserdata(state, 2)));
    self.setAnimation(self.animationStack.getLastItem(), true);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSpriter, removeAnimations)
{
    self.animationStack.setSize(0);
    self.animation = nullptr;
}
ENTITY_COMPONENT_END()

void ComponentSpriter::setAnimation(const graphics::SpriterManagerItem * _animation, const bool reset_time)
{
    animation = _animation;

    if(reset_time)
    {
        currentTime = 0.0f;
    }

    if(lastSpriterEntity != & animation->getEntity())
    {
        characterMap = nullptr;
        lastSpriterEntity = & animation->getEntity();
    }
}

}
}
