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

    ENTITY_COMPONENT_METHOD_DECLARE(reset);

protected:
    graphics::ParticleSystem
        particleSystem;
    uint
        worldIndex,
        size;
};

}
}
