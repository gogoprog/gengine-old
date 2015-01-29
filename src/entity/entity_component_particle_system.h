#pragma once

#include "script.h"
#include "graphics_particle_system.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentParticleSystem
{
public:
    ComponentParticleSystem();

    ENTITY_COMPONENT_DECLARE();

protected:
    graphics::ParticleSystem
        particleSystem;
    uint
        worldIndex,
        size;
};

}
}
