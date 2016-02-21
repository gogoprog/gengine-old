#include "entity_component_spriter.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "graphics_animation.h"
#include "entity_system.h"
#include "entity_entity.h"
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

void ComponentSpriter::init()
{
}

void ComponentSpriter::insert()
{
    graphics::System::getInstance().getWorld(worldIndex).addObject(spriteGroup);
}

void ComponentSpriter::update(const float dt)
{
    Transform & transform = entity->transform;

    spriteGroup.setPosition(transform.position);
    spriteGroup.setRotation(transform.rotation);

    if(animation)
    {
        float duration = animation->getDuration();
        bool looping = animation->isLooping();


        currentTime += System::getInstance().getCurrentDt() * timeFactor;

        if(currentTime > duration)
        {
            while(currentTime > duration)
            {
                currentTime -= duration;
            }

            if(!looping)
            {
                animationStack.removeLastItem();

                if(animationStack.getSize() > 0)
                {
                    setAnimation(animationStack.getLastItem(), false);
                }
                else
                {
                    currentTime = duration;
                }
            }
        }

        const auto & animation_animation = animation->getAnimation();

        currentUintTime = uint(currentTime * 1000) % animation_animation.length;

        Pointer<const graphics::SpriterMainlineKey> mlk = & animation_animation.getMainlineKey(currentUintTime);

        if(currentMainlineKey != mlk)
        {
            currentMainlineKey = mlk;
            animation->fill(spriteGroup, *mlk, characterMap);
        }

        animation->update(spriteGroup, *mlk, currentTime, characterMap, transform.scale);

        if(!looping && currentTime == duration && !animationStack.getSize())
        {
            animation = nullptr;
        }

        for(const auto & event : animation_animation.events)
        {
            if(event.time > previousUintTime && event.time <= currentUintTime)
            {
                auto state = script::System::getInstance().getState();
                lua_getfield(state, -1, "fireEvent");
                lua_pushvalue(state, -2);
                lua_pushstring(state, "SpriterEvent");
                lua_pushstring(state, event.name.c_str());
                script::System::getInstance().call(3, 0);
            }
        }

        previousUintTime = currentUintTime;
    }
}

void ComponentSpriter::remove()
{
    graphics::System::getInstance().getWorld(worldIndex).removeObject(spriteGroup);
}

ENTITY_COMPONENT_IMPLEMENT(ComponentSpriter)
{
    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        pushAnimation,
        {
            SCRIPT_GET_SELF(ComponentSpriter);
            self.animationStack.add(static_cast<const graphics::SpriterManagerItem *>(lua_touserdata(state, 2)));
            self.setAnimation(self.animationStack.getLastItem(), true);
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        removeAnimations,
        {
            SCRIPT_GET_SELF(ComponentSpriter);
            self.animationStack.setSize(0);
            self.animation = nullptr;
            return 0;
        }
        );

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        getBoneLocalTransform,
        {
            SCRIPT_GET_SELF(ComponentSpriter);

            if(self.currentMainlineKey)
            {
                uint bone_index;
                math::Transform result;

                script::get(state, bone_index, 2);

                self.animation->getBoneTransform(result, *self.currentMainlineKey, self.currentTime, bone_index);

                script::push(state, result);

                return 1;
            }

            lua_pushnil(state);

            return 1;
        }
        );
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
