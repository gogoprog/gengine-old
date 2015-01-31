#pragma once

#include "primitives.h"
#include "vector2.h"
#include "stack.h"
#include "array.h"
#include "pointer.h"
#include "graphics_uniform.h"
#include "graphics_world.h"
#include "graphics_program.h"
#include "graphics_vertex_buffer.h"
#include "graphics_index_buffer.h"
#include "graphics_shader.h"
#include "graphics_vertex.h"
#include "graphics_particle_modifier_uniforms.h"

namespace gengine
{
namespace graphics
{

class World;

class Renderer
{
public:
    friend class System;

    enum class Type
    {
        SPRITE,
        SPRITE_BATCH,
        PARTICLE_SYSTEM,
        NONE
    };

    Renderer();
    void init();
    void finalize();
    void render(const World & world);

private:
    void enable(const Type type, const World & world);

    Shader
        defaultVertexShader,
        defaultFragmentShader,
        particleVertexShader,
        particleFragmentShader;
    Program
        defaultProgram,
        particleProgram;
    VertexBuffer<Vertex>
        vertexBufferQuad;
    IndexBuffer
        indexBufferQuad;
    Uniform
        projectionMatrixUniform,
        transformMatrixUniform,
        samplerUniform,
        colorUniform,
        uvScaleUniform,
        uvOffsetUniform,
        particleProjectionMatrixUniform,
        particleTransformMatrixUniform,
        particleSamplerUniform,
        particleColorUniform;
    ParticleModifierUniforms
        particleColorUniforms,
        particleScaleUniforms;
    Type
        currentType;
    Pointer<Program>
        currentProgram;
};

}
}
