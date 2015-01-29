#include "graphics_particle_system.h"

#include "graphics_renderer.h"

namespace gengine
{
namespace graphics
{

ParticleSystem::ParticleSystem()
    :
    Object(),
    currentTime(0.0f),
    particleToEmitSum(0.0f),
    texture()
{
}

Renderer::Type ParticleSystem::getRenderType()
{
    return Renderer::Type::PARTICLE_SYSTEM;
}

void ParticleSystem::init(const uint maximum_particle_count)
{
    maximumParticleCount = maximum_particle_count;

    particles.positions = new Vector2[maximumParticleCount];
    particles.velocities = new Vector2[maximumParticleCount];
    particles.lifeTimes = new float[maximumParticleCount];
    particles.maxLifeTimes = new float[maximumParticleCount];
}

void ParticleSystem::update(const float dt)
{
    Vector2
        * positions = particles.positions,
        * velocities = particles.velocities;
    float
        * lifeTimes = particles.lifeTimes,
        * maxLifeTimes = particles.maxLifeTimes;

    if(currentTime<emitterLifeTime)
    {
        uint count;

        particleToEmitSum += emitterRate * dt;

        count = uint(particleToEmitSum);

        if(count > 0)
        {
            if(particleCount < maximumParticleCount)
            {
                addParticle();
            }

            particleToEmitSum -= count;
        }
    }

    currentTime += dt;

    for(uint i=0; i<particleCount;++i)
    {
        lifeTimes[i] += dt;

        if(lifeTimes[i] >= maxLifeTimes[i])
        {
            removeParticle(i);
        }
    }

    for(uint i=0; i<particleCount;++i)
    {
        positions[i] += velocities[i] * dt;
    }
}

void ParticleSystem::finalize()
{
    delete particles.positions;
    delete particles.velocities;
    delete particles.lifeTimes;
    delete particles.maxLifeTimes;
}

void ParticleSystem::addParticle()
{
    particleCount++;
    particles.positions[particleCount].set(0.0f, 0.0f);
    particles.velocities[particleCount].set(0.0f, 0.0f);
    particles.lifeTimes[particleCount] = 0.0f;
    particles.maxLifeTimes[particleCount] = lifeTimeRange.getRandomInRange();
}

void ParticleSystem::removeParticle(const uint index)
{
    particleCount--;

    particles.positions[index] = particles.positions[particleCount];
    particles.velocities[index] = particles.velocities[particleCount];
    particles.lifeTimes[index] = particles.lifeTimes[particleCount];
    particles.maxLifeTimes[index] = particles.maxLifeTimes[particleCount];
}

}
}
