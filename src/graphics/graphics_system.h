#pragma once

#include "graphics_program.h"
#include "graphics_vertex_buffer.h"
#include "graphics_index_buffer.h"
#include "graphics_uniform.h"
#include "graphics_shader.h"
#include "graphics_texture.h"
#include "array.h"

namespace gengine
{
namespace graphics
{

class World;

class System
{
public:
    SINGLETON(System);
    void init();
    void finalize();
    void test(const float dt);

    World & getWorld(const uint index = 0);

    struct Vertex
    {
        float x, y;
        float u, v;
    };
private:
    Shader defaultVertexShader, defaultFragmentShader;
    Program defaultProgram;
    VertexBuffer<Vertex> vertexBufferQuad;
    IndexBuffer indexBufferQuad;
    Uniform projectionMatrixUniform, transformMatrixUniform, samplerUniform, colorUniform;
    Texture defaultTexture;

    Array<World *> worldTable;
};

}
}
