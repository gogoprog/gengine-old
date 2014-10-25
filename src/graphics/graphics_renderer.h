#pragma once

#include "primitives.h"
#include "vector2.h"
#include "stack.h"
#include "array.h"
#include "graphics_uniform.h"
#include "graphics_world.h"
#include "graphics_program.h"
#include "graphics_vertex_buffer.h"
#include "graphics_index_buffer.h"
#include "graphics_shader.h"

namespace gengine
{
namespace graphics
{

class World;

class Renderer
{
public:
    friend class System;

    struct Vertex
    {
        float x, y;
        float u, v;
    };

    enum class Type
    {
        SPRITE,
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
        defaultFragmentShader;
    Program
        defaultProgram;
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
        uvOffsetUniform;
    Type
        currentType;
};

}
}