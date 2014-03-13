#include "graphics_system.h"

#include "debug.h"
#include "memory.h"
#include "graphics_opengl.h"
#include "graphics_program.h"
#include "graphics_shader.h"

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
    "varying vec4 v_color;\n"
    //"uniform mat4 projectionMatrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 res = vec4(vertex,1.0,1.0);\n"
    "    res.xy *= 0.5;\n"
    "    gl_Position = res;\n"
    "    v_color = color;\n"
    "}";
const char fragment_shader_source[] =
    "varying " PRECISION "vec4 v_color;\n"
    //"varying " PRECISION "vec2 v_texCoord;\n"
    //"uniform sampler2D tex0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(1.0,1.0,1.0,1.0) * v_color; //texture2D(tex0, v_texCoord) * v_color;\n"
    "}";

void System::init()
{
    glViewport(0, 0, 640, 480);

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
}

void System::test()
{
    GLuint vbo, vboi;
    Vertex vertices[4];
    ushort indices[6];

    memset(vertices, 255, sizeof(Vertex) * 4);

    vertices[0].x = -1.0f;
    vertices[0].y = 1.0f;
    vertices[0].r = 1.0f;

    vertices[1].x = 1.0f;
    vertices[1].y = 1.0f;

    vertices[2].x = 1.0f;
    vertices[2].y = -1.0f;

    vertices[3].x = -1.0f;
    vertices[3].y = -1.0f;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    defaultProgram.use();

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + 8);

    glGenBuffers(1, &vboi);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort) * 6, indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vboi);
}

}
}
