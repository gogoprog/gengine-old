#pragma once

#include "primitives.h"
#include "vector2.h"
#include "vector4.h"
#include "matrix3.h"
#include "pointer.h"
#include "range.h"
#include "graphics_object.h"
#include "graphics_particle_vertex.h"
#include "graphics_vertex_buffer.h"

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
        MAXIMUM_STEP_COUNT = 8,
        MAXIMUM_PARTICLE_COUNT = VertexBuffer<ParticleVertex>::MAXIMUM_VERTEX_COUNT / 4
    };

    ParticleSystem();

    virtual Renderer::Type getRenderType() override;

    void init(const uint maximum_particle_count);
    void update(const float dt);
    void finalize();
    void reset();

    bool keepsLocal() const { return itKeepsLocal; }
    void setKeepsLocal(const bool value) { itKeepsLocal = value; }

    void setEmitterLifeTime(const float value) { emitterLifeTime = value; }
    void setEmitterRate(const float value) { emitterRate = value; }
    void setTexture(const Texture & _texture) { texture = & _texture; }
    void setLifeTimeRange(const Range<float> & value) { lifeTimeRange = value; }
    void setDirectionRange(const Range<float> & value) { directionRange = value; }
    void setSpeedRange(const Range<float> & value) { speedRange = value; }
    void setRotationRange(const Range<float> & value) { rotationRange = value; }
    void setSpinRange(const Range<float> & value) { spinRange = value; }
    void setExtentRange(const Range<Vector2> & value) { extentRange = value; }
    void setLinearAccelerationRange(const Range<Vector2> & value) { linearAccelerationRange = value; }

    Array<Vector2> & getScaleTable() { return scaleTable; }
    Array<Vector4> & getColorTable() { return colorTable; }

private:
    struct ParticleTable
    {
        Vector2
            * positions,
            * velocities,
            * extents,
            * linearAccelerations;
        float
            * lifeTimes,
            * maxLifeTimes,
            * rotations,
            * spins;
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
    bool
        itKeepsLocal;
    Pointer<const Texture>
        texture;
    ParticleTable
        particles;
    Range<float>
        lifeTimeRange,
        directionRange,
        speedRange,
        rotationRange,
        spinRange;
    Range<Vector2>
        extentRange,
        linearAccelerationRange;
    VertexBuffer<ParticleVertex>
        vertexBuffer;
    Array<Vector2>
        scaleTable;
    Array<Vector4>
        colorTable;
};

}
}
