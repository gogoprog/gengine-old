#pragma once

#include "graphics_program.h"
#include "graphics_vertex_buffer.h"
#include "graphics_index_buffer.h"
#include "graphics_uniform.h"
#include "graphics_shader.h"
#include "graphics_texture.h"
#include "graphics_camera.h"
#include "graphics_sprite.h"
#include "script.h"
#include "array.h"

namespace gengine
{
namespace graphics
{

class World;

class System
{
public:
    struct Vertex
    {
        float x, y;
        float u, v;
    };

    SINGLETON(System);
    void init();
    void finalize();
    void update();
    void render();
    void setClearColor(const Vector4 & color);

    World & getWorld(const uint index = 0);

    Program & getDefaultProgram() { return defaultProgram; }
    VertexBuffer<Vertex> & getVertexBufferQuad() { return vertexBufferQuad; }
    IndexBuffer & getIndexBufferQuad() { return indexBufferQuad; }
    Camera & getDefaultCamera() { return defaultCamera; }
    const Texture & getDefaultTexture() const { return defaultTexture; }

    static SCRIPT_REGISTERER();

private:
    Shader
        defaultVertexShader,
        defaultFragmentShader;
    Program
        defaultProgram;
    VertexBuffer<Vertex>
        vertexBufferQuad;
    IndexBuffer
        indexBufferQuad;
    Texture
        defaultTexture;
    Camera
        defaultCamera;
    Array<World *>
        worldTable;
};

}
}
