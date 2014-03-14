#pragma once

#include "graphics_program.h"
#include "graphics_vertex_buffer.h"
#include "graphics_index_buffer.h"
#include "graphics_uniform.h"

namespace gengine
{
namespace graphics
{

class System
{
public:
    SINGLETON(System);
    void init();
    void test(const float dt);

    struct Vertex
    {
        float x, y;
        float r, g, b, a;
        float s, t;
    };

private:
    Program defaultProgram;
    VertexBuffer<Vertex> vertexBufferQuad;
    IndexBuffer indexBufferQuad;
    Uniform transformMatrixUniform;
};

}
}
