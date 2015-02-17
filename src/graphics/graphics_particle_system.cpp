#include "graphics_particle_system.h"

#include "graphics_renderer.h"
#include "debug.h"

namespace gengine
{
namespace graphics
{

ParticleSystem::ParticleSystem()
    :
    Object(),
    currentTime(0.0f),
    particleToEmitSum(0.0f),
    particleCount(0),
    itKeepsLocal(true),
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
    particles.extents = new Vector2[maximumParticleCount];
    particles.linearAccelerations = new Vector2[maximumParticleCount];
    particles.lifeTimes = new float[maximumParticleCount];
    particles.maxLifeTimes = new float[maximumParticleCount];
    particles.rotations = new float[maximumParticleCount];
    particles.spins = new float[maximumParticleCount];

    vertexBuffer.init(maximumParticleCount * 4, true);
}

void ParticleSystem::update(const float dt)
{
    Vector2
        * positions = particles.positions,
        * extents = particles.extents,
        * velocities = particles.velocities,
        * linearAccelerations = particles.linearAccelerations;
    float
        * lifeTimes = particles.lifeTimes,
        * maxLifeTimes = particles.maxLifeTimes,
        * rotations = particles.rotations,
        * spins = particles.spins;
    ParticleVertex
        * vertices;

    if(currentTime<emitterLifeTime)
    {
        uint count;

        particleToEmitSum += emitterRate * dt;

        count = uint(particleToEmitSum);

        if(count > 0)
        {
            for(uint i=0; i<count; ++i)
            {
                if(particleCount < maximumParticleCount)
                {
                    addParticle();
                }
            }

            particleToEmitSum -= count;
        }
    }

    currentTime += dt;

    for(uint p=0; p<particleCount; ++p)
    {
        lifeTimes[p] += dt;

        if(lifeTimes[p] >= maxLifeTimes[p])
        {
            removeParticle(p);
        }
    }

    for(uint p=0; p<particleCount; ++p)
    {
        positions[p] += velocities[p] * dt;
    }

    for(uint p=0; p<particleCount; ++p)
    {
        velocities[p] += linearAccelerations[p] * dt;
    }

    for(uint p=0; p<particleCount; ++p)
    {
        rotations[p] += spins[p] * dt;
    }

    vertices = vertexBuffer.map();

    for(uint p=0; p<particleCount; ++p)
    {
        float life = lifeTimes[p] / maxLifeTimes[p];

        for(uint i=0; i<4; ++i)
        {
            vertices[p*4 + i].index = float(i);
            vertices[p*4 + i].position = positions[p];
            vertices[p*4 + i].extent = extents[p];
            vertices[p*4 + i].rotation = rotations[p];
            vertices[p*4 + i].life = life;
        }
    }

    vertexBuffer.unMap();
}

void ParticleSystem::finalize()
{
    delete particles.positions;
    delete particles.extents;
    delete particles.velocities;
    delete particles.linearAccelerations;
    delete particles.lifeTimes;
    delete particles.maxLifeTimes;
}

void ParticleSystem::addParticle()
{
    float direction = directionRange.getRandom();
    float speed = speedRange.getRandom();

    particles.positions[particleCount].set(0.0f, 0.0f);

    if(!itKeepsLocal)
    {
        particles.positions[particleCount] += position;
    }

    particles.extents[particleCount] = extentRange.getRandom();
    particles.velocities[particleCount].set(- std::cos(direction) * speed, std::sin(direction) * speed);
    particles.linearAccelerations[particleCount] = linearAccelerationRange.getRandom();
    particles.lifeTimes[particleCount] = 0.0f;
    particles.maxLifeTimes[particleCount] = lifeTimeRange.getRandom();
    particles.rotations[particleCount] = rotationRange.getRandom();
    particles.spins[particleCount] = spinRange.getRandom();

    particleCount++;
}

void ParticleSystem::removeParticle(const uint index)
{
    particleCount--;

    particles.positions[index] = particles.positions[particleCount];
    particles.extents[index] = particles.extents[particleCount];
    particles.velocities[index] = particles.velocities[particleCount];
    particles.linearAccelerations[index] = particles.linearAccelerations[particleCount];
    particles.lifeTimes[index] = particles.lifeTimes[particleCount];
    particles.maxLifeTimes[index] = particles.maxLifeTimes[particleCount];
    particles.rotations[index] = particles.rotations[particleCount];
    particles.spins[index] = particles.spins[particleCount];
}

}
}
