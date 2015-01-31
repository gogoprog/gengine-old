#pragma once

#include "primitives.h"
#include "vector2.h"
#include "vector4.h"
#include "matrix3.h"
#include "graphics_object.h"
#include "pointer.h"
#include "graphics_particle_vertex.h"
#include <cmath>

namespace gengine
{
namespace graphics
{

class ParticleSystem : public Object
{
friend class Renderer;

public:
    enum
    {
        MAXIMUM_STEP_COUNT = 8
    };

    ParticleSystem();

    virtual Renderer::Type getRenderType() override;

    void init(const uint maximum_particle_count);
    void update(const float dt);
    void finalize();

    void setEmitterLifeTime(const float value) { emitterLifeTime = value; }
    void setEmitterRate(const float value) { emitterRate = value; }
    void setTexture(const Texture & _texture) { texture = & _texture; }
    void setLifeTimeRange(const Vector2 & value) { lifeTimeRange = value; }

private:
    struct ParticleTable
    {
        Vector2
            * positions,
            * velocities,
            * extents;
        float
            * lifeTimes,
            * maxLifeTimes;
    };

    void addParticle();
    void removeParticle(const uint index);

    float
        emitterLifeTime,
        emitterRate,
        currentTime,
        particleToEmitSum;
    uint
        particleCount,
        maximumParticleCount;
    Pointer<const Texture>
        texture;
    ParticleTable
        particles;
    Vector2
        lifeTimeRange;
    VertexBuffer<ParticleVertex>
        vertexBuffer;
    Array<Vector2>
        scaleTable;
    Array<Vector4>
        colorTable;
};

}
}
