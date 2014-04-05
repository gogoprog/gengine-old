#include "graphics_system.h"

#include "debug.h"
#include "memory.h"
#include "graphics_opengl.h"
#include "graphics_program.h"
#include "graphics_shader.h"
#include "graphics_vertex_buffer.h"
#include "graphics_world.h"
#include "graphics_texture_manager.h"
#include "vector4.h"
#include "application.h"
#include <math.h>

namespace gengine
{
namespace graphics
{

const char vertex_shader_source[] = GL_GLSL(
    attribute vec2 position;
    attribute vec2 texCoords;
    varying highp vec2 v_texCoords;
    uniform highp mat3 projectionMatrix;
    uniform highp mat3 transformMatrix;
    uniform highp vec2 uvScale;
    uniform highp vec2 uvOffset;

    void main()
    {
        vec3 res = transformMatrix * vec3(position,1.0 ) * projectionMatrix;
        v_texCoords.x = texCoords.x * uvScale.x + uvOffset.x;
        v_texCoords.y = texCoords.y * uvScale.y + uvOffset.y;
        gl_Position = vec4(res,1.0);
    }
);

const char fragment_shader_source[] = GL_GLSL(
    varying highp vec2 v_texCoords;
    uniform sampler2D tex0;
    uniform highp vec4 color;

    void main()
    {
        gl_FragColor = texture2D(tex0, v_texCoords) * color;
    }
);

void System::init()
{
    geDebugLog("graphics::System::init()");

    Vertex vertices[4];
    ushort indices[6];

    defaultVertexShader.init(GL_VERTEX_SHADER);
    defaultVertexShader.compile(vertex_shader_source);

    defaultFragmentShader.init(GL_FRAGMENT_SHADER);
    defaultFragmentShader.compile(fragment_shader_source);

    defaultProgram.init();
    defaultProgram.attachShader(defaultVertexShader);
    defaultProgram.attachShader(defaultFragmentShader);
    defaultProgram.link();

    vertices[0].x = -0.5f;
    vertices[0].y = 0.5f;
    vertices[0].u = 0.0f;
    vertices[0].v = 0.0f;

    vertices[1].x = 0.5f;
    vertices[1].y = 0.5f;
    vertices[1].u = 1.0f;
    vertices[1].v = 0.0f;

    vertices[2].x = 0.5f;
    vertices[2].y = -0.5f;
    vertices[2].u = 1.0f;
    vertices[2].v = 1.0f;

    vertices[3].x = -0.5f;
    vertices[3].y = -0.5f;
    vertices[3].u = 0.0f;
    vertices[3].v = 1.0f;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    vertexBufferQuad.init();
    vertexBufferQuad.setData(vertices, 4);

    indexBufferQuad.init();
    indexBufferQuad.setData(indices, 6);

    TextureManager::getInstance().init();

    defaultCamera.setExtent(application::getExtent());

    setClearColor(Vector4(0.2f,0.2f,0.2f,1.0f));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    createWorlds(1);
}

void System::finalize()
{
    geDebugLog("graphics::System::finalize()");

    for(World * world : worldTable)
    {
        world->finalize();
    }

    TextureManager::getInstance().finalize();

    defaultProgram.finalize();
    defaultFragmentShader.finalize();
    defaultVertexShader.finalize();
    vertexBufferQuad.finalize();
    indexBufferQuad.finalize();
}

void System::update()
{
    for(World * world : worldTable)
    {
        world->update();
    }
}

void System::render()
{
    for(World * world : worldTable)
    {
        world->render();
    }
}

void System::setClearColor(const Vector4 & c)
{
    glClearColor(c.x, c.y ,c.z, c.w);
}

void System::createWorlds(const uint count)
{
    int new_count = count - worldTable.getSize();

    for(int i=0; i<new_count; ++i)
    {
        World * world = new World();
        world->init();
        worldTable.add(world);
    }
}

World & System::getWorld(const uint index)
{
    return * worldTable[index];
}

SCRIPT_CLASS_REGISTERER(System)
{
}

}
}
