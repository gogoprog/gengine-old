#include "entity_component_particle_system.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"

namespace gengine
{
namespace entity
{

ComponentParticleSystem::ComponentParticleSystem()
    :
    worldIndex(0),
    size(128)
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentParticleSystem)
{
    ENTITY_COMPONENT_PUSH_FUNCTION(reset);
}

ENTITY_COMPONENT_SETTERS(ComponentParticleSystem)
{
    ENTITY_COMPONENT_SETTER_FIRST(layer)
    {
        self.particleSystem.setLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(texture)
    {
        graphics::Texture * texture = static_cast<graphics::Texture *>(lua_touserdata(state, 3));
        self.particleSystem.setTexture(*texture);
    }
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER(size)
    {
        self.size = uint(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(keepLocal)
    {
        self.particleSystem.setKeepsLocal(lua_toboolean(state,3));
    }
    ENTITY_COMPONENT_SETTER(emitterRate)
    {
        self.particleSystem.setEmitterRate(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(emitterLifeTime)
    {
        self.particleSystem.setEmitterLifeTime(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(extentRange)
    {
        Range<Vector2> range;

        Range<Vector2>::fill(state, range, 3);

        self.particleSystem.setExtentRange(range);
    }
    ENTITY_COMPONENT_SETTER(linearAccelerationRange)
    {
        Range<Vector2> range;

        Range<Vector2>::fill(state, range, 3);

        self.particleSystem.setLinearAccelerationRange(range);
    }
    ENTITY_COMPONENT_SETTER(lifeTimeRange)
    {
        Range<float> range;

        Range<float>::fill(state, range, 3);

        self.particleSystem.setLifeTimeRange(range);
    }
    ENTITY_COMPONENT_SETTER(directionRange)
    {
        Range<float> range;

        Range<float>::fill(state, range, 3);

        self.particleSystem.setDirectionRange(range);
    }
    ENTITY_COMPONENT_SETTER(speedRange)
    {
        Range<float> range;

        Range<float>::fill(state, range, 3);

        self.particleSystem.setSpeedRange(range);
    }
    ENTITY_COMPONENT_SETTER(rotationRange)
    {
        Range<float> range;

        Range<float>::fill(state, range, 3);

        self.particleSystem.setRotationRange(range);
    }
    ENTITY_COMPONENT_SETTER(spinRange)
    {
        Range<float> range;

        Range<float>::fill(state, range, 3);

        self.particleSystem.setSpinRange(range);
    }
    ENTITY_COMPONENT_SETTER(scales)
    {
        Vector2 value;

        self.particleSystem.getScaleTable().setSize(0);

        lua_pushnil(state);

        while (lua_next(state, 3) != 0)
        {
            Vector2::fill(state, value, -1);
            self.particleSystem.getScaleTable().add(value);
            lua_pop(state, 1);
        }

        lua_pop(state, 1);
    }
    ENTITY_COMPONENT_SETTER(colors)
    {
        Vector4 value;

        self.particleSystem.getColorTable().setSize(0);

        lua_pushnil(state);

        while (lua_next(state, 3) != 0)
        {
            Vector4::fill(state, value, -1);
            self.particleSystem.getColorTable().add(value);
            lua_pop(state, 1);
        }

        lua_pop(state, 1);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentParticleSystem, init)
{
    SCRIPT_GET_SELF(ComponentParticleSystem);

    self.particleSystem.init(self.size);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentParticleSystem, insert)
{
    SCRIPT_GET_SELF(ComponentParticleSystem);

    graphics::System::getInstance().getWorld(self.worldIndex).addObject(self.particleSystem);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentParticleSystem, update)
{
    graphics::ParticleSystem & particleSystem = self.particleSystem;

    particleSystem.update(System::getInstance().getCurrentDt());

    Transform transform;
    fillTransformFromComponent(state, transform);

    particleSystem.setPosition(transform.position);
    particleSystem.setRotation(transform.rotation);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentParticleSystem, remove)
{
    graphics::System::getInstance().getWorld(self.worldIndex).removeObject(self.particleSystem);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentParticleSystem, reset)
{
    self.particleSystem.reset();
}
ENTITY_COMPONENT_END()

}
}
