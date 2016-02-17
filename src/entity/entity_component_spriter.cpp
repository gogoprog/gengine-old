#include "entity_component_spriter.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "graphics_animation.h"
#include "entity_system.h"
#include "script.h"
#include "script_system.h"
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
    timeFactor(1.0f),
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
    ENTITY_COMPONENT_SETTER(timeFactor)
    {
        self.timeFactor = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER(color)
    {
        Vector4::fill(state, self.spriteGroup.getColor(), 3);
    }
    ENTITY_COMPONENT_SETTER(alpha)
    {
        self.spriteGroup.setColorAlpha(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(characterMap)
    {
        if(self.lastSpriterEntity)
        {
            self.characterMap = self.lastSpriterEntity->getCharacterMap(lua_tostring(state,3));
        }
        else
        {
            self.characterMapName = lua_tostring(state,3);
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
    graphics::SpriteGroup & spriteGroup = self.spriteGroup;
    Transform transform;

    getTransformFromComponent(state, transform);

    spriteGroup.setPosition(transform.position);
    spriteGroup.setRotation(transform.rotation);

    if(self.animation)
    {
        float duration = self.animation->getDuration();
        bool looping = self.animation->isLooping();


        self.currentTime += System::getInstance().getCurrentDt() * self.timeFactor;

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

        const auto & animation = self.animation->getAnimation();

        self.currentUintTime = uint(self.currentTime * 1000) % animation.length;

        Pointer<const graphics::SpriterMainlineKey> mlk = & animation.getMainlineKey(self.currentUintTime);

        if(self.currentMainlineKey != mlk)
        {
            self.currentMainlineKey = mlk;
            self.animation->fill(spriteGroup, *mlk, self.characterMap);
        }

        self.animation->update(spriteGroup, *mlk, self.currentTime, self.characterMap, transform.scale);

        if(!looping && self.currentTime == duration && !self.animationStack.getSize())
        {
            self.animation = nullptr;
        }

        for(const auto & event : animation.events)
        {
            if(event.time > self.previousUintTime && event.time <= self.currentUintTime)
            {
                lua_getfield(state, 1, "entity");
                lua_getfield(state, -1, "fireEvent");
                lua_pushvalue(state, -2);
                lua_pushstring(state, "SpriterEvent");
                lua_pushstring(state, event.name.c_str());
                script::System::getInstance().call(3, 0);
                lua_pop(state, 1);
            }
        }

        self.previousUintTime = self.currentUintTime;
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
        previousUintTime = 0;
    }

    if(lastSpriterEntity != & animation->getEntity())
    {
        characterMap = nullptr;
        lastSpriterEntity = & animation->getEntity();

        if(characterMapName != "")
        {
            characterMap = lastSpriterEntity->getCharacterMap(characterMapName.c_str());
            characterMapName = "";
        }
    }
}

}
}
