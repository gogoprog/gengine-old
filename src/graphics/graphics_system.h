#pragma once

#include "graphics_program.h"
#include "graphics_vertex_buffer.h"
#include "graphics_index_buffer.h"
#include "graphics_camera.h"
#include "graphics_renderer.h"
#include "script.h"
#include "array.h"
#include "graphics_vertex.h"

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
    void update();
    void render();
    void setClearColor(const Vector4 & color);
    void createWorlds(const uint count);

    World & getWorld(const uint index);

    VertexBuffer<Vertex> & getVertexBufferQuad() { return renderer.vertexBufferQuad; }
    IndexBuffer & getIndexBufferQuad() { return renderer.indexBufferQuad; }

    Camera & getDefaultCamera() { return defaultCamera; }

private:
    Camera
        defaultCamera;
    Array<World *>
        worldTable;
    Renderer
        renderer;
};

}
}
