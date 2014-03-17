#include "graphics_system.h"

#include "debug.h"
#include "memory.h"
#include "graphics_opengl.h"
#include "graphics_program.h"
#include "graphics_shader.h"
#include "graphics_vertex_buffer.h"
#include "graphics_world.h"
#include "vector4.h"
#include <math.h>

namespace gengine
{
namespace graphics
{

#ifdef EMSCRIPTEN
#define PRECISION " highp "
#else
#define PRECISION
#endif

const char vertex_shader_source[] =
    "attribute vec2 position;\n"
    "attribute vec2 texCoords;\n"
    "varying " PRECISION "vec2 v_texCoords;\n"
    "uniform " PRECISION "mat3 projectionMatrix;\n"
    "uniform " PRECISION "mat3 transformMatrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec3 res = transformMatrix * vec3(position,1.0 ) * projectionMatrix;\n"
    "    v_texCoords = texCoords;\n"
    "    gl_Position = vec4(res,1.0);\n"
    "}";
const char fragment_shader_source[] =
    "varying " PRECISION "vec2 v_texCoords;\n"
    "uniform sampler2D tex0;\n"
    "uniform " PRECISION "vec4 color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = texture2D(tex0, v_texCoords) * color;\n"
    "}";

#undef PRECISION

void System::init()
{
    geLog("graphics::System::init()");

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

    projectionMatrixUniform.init(defaultProgram, "projectionMatrix");
    transformMatrixUniform.init(defaultProgram, "transformMatrix");
    samplerUniform.init(defaultProgram, "tex0");
    colorUniform.init(defaultProgram, "color");

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

    defaultTexture.init();
    defaultTexture.setFromFile("bird.png");

    defaultCamera.setExtent(Vector2(640.0f, 480.0f));

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);

    {
        World * world = new World();
        world->init();
        worldTable.add(world);

        testSprite.setPosition(Vector2(0.0f,0.0f));
        testSprite.setExtent(Vector2(256.0f,256.0f));
        testSprite.setTexture(defaultTexture);

        world->addSprite(testSprite);
    }

}

void System::finalize()
{
    geLog("graphics::System::finalize()");

    for(World * world : worldTable)
    {
        world->finalize();
    }

    defaultTexture.finalize();
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

void System::test(const float dt)
{
    static float total = 0;
    total += dt * 3;

    testSprite.setRotation(total);
}

World & System::getWorld(const uint index)
{
    return * worldTable[index];
}

}
}
