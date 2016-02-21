#pragma once

#include "script.h"
#include "graphics_particle_system.h"
#include "entity_macros.h"
#include "entity_component.h"

namespace gengine
{
namespace entity
{

class ComponentParticleSystem : public Component
{
public:
    ComponentParticleSystem();

    virtual void init() override;
    virtual void insert() override;
    virtual void update(const float dt) override;
    virtual void remove() override;

    ENTITY_COMPONENT_DECLARE_OLD(ComponentParticleSystem);

protected:
    graphics::ParticleSystem
        particleSystem;
    uint
        worldIndex,
        size;
};

}
}
