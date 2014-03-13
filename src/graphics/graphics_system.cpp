#include "graphics_system.h"

#include "debug.h"
#include "memory.h"
#include "graphics_opengl.h"
#include "graphics_program.h"
#include "graphics_shader.h"
#include "graphics_vertex_buffer.h"

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
    "attribute vec2 vertex;\n"
    "attribute vec4 color;\n"
    "varying " PRECISION "vec4 v_color;\n"
    "uniform " PRECISION "mat3 transformMatrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 res = vec4( transformMatrix * vec3(vertex,1.0 ),1.0);\n"
    "    res.xy *= 0.5;\n"
    "    v_color = color;\n"
    "    gl_Position = res;\n"
    "}";
const char fragment_shader_source[] =
    "varying " PRECISION "vec4 v_color;\n"
    //"varying " PRECISION "vec2 v_texCoord;\n"
    //"uniform sampler2D tex0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = v_color; //texture2D(tex0, v_texCoord) * v_color;\n"
    "}";

#undef PRECISION

void System::init()
{
    Vertex vertices[4];
    ushort indices[6];

    Shader vertex_shader, fragment_shader;
    geLog("Creating default programs");

    vertex_shader.init(GL_VERTEX_SHADER);
    vertex_shader.compile(vertex_shader_source);

    fragment_shader.init(GL_FRAGMENT_SHADER);
    fragment_shader.compile(fragment_shader_source);

    defaultProgram.init();
    defaultProgram.attachShader(vertex_shader);
    defaultProgram.attachShader(fragment_shader);
    defaultProgram.link();

    vertices[0].x = -1.0f;
    vertices[0].y = 1.0f;

    vertices[0].r = 1.0f;
    vertices[0].g = 1.0f;
    vertices[0].b = 0.0f;
    vertices[0].a = 1.0f;

    vertices[1].x = 1.0f;
    vertices[1].y = 1.0f;

    vertices[1].r = 1.0f;
    vertices[1].g = 1.0f;
    vertices[1].b = 1.0f;
    vertices[1].a = 1.0f;

    vertices[2].x = 1.0f;
    vertices[2].y = -1.0f;

    vertices[2].r = 1.0f;
    vertices[2].g = 1.0f;
    vertices[2].b = 1.0f;
    vertices[2].a = 1.0f;

    vertices[3].x = -1.0f;
    vertices[3].y = -1.0f;

    vertices[3].r = 0.0f;
    vertices[3].g = 0.0f;
    vertices[3].b = 0.0f;
    vertices[3].a = 1.0f;

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
}

void System::test(const float dt)
{
    Matrix3 m;
    static float total = 0;
    total += dt;

    m.setIdentity();
    m.setTranslation(total,0);

    defaultProgram.use();

    uint location = glGetUniformLocation(defaultProgram.getId(), "transformMatrix");
    geLog( "loc:" << location );

    defaultProgram.setUniform(location, m);
    GL_CHECK();

    vertexBufferQuad.apply();
    indexBufferQuad.draw();
}

}
}
