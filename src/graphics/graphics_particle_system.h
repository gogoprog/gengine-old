#pragma once

#include "primitives.h"
#include "vector2.h"
#include "vector4.h"
#include "matrix3.h"
#include "graphics_object.h"
#include "pointer.h"

namespace gengine
{
namespace graphics
{

class ParticleSystem : public Object
{
friend class Renderer;

public:
    ParticleSystem();

    virtual Renderer::Type getRenderType() override;

    void init(const uint maximum_particle_count);
    void update(const float dt);
    void finalize();

    void setTexture(const Texture & _texture) { texture = & _texture; }

private:
    struct ParticleTable
    {
        Vector2
            * positions,
            * velocities;
        float
            * lifeTimes,
            * maxLifeTimes;
    };

    void removeParticle(const uint index);

    float
        lifeTime,
        rate,
        currentTime;
    uint
        particleCount,
        maximumParticleCount;
    Pointer<const Texture>
        texture;
    ParticleTable
        particles;
};

}
}
