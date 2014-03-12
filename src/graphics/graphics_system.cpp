#include "graphics_system.h"

#include "debug.h"
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
    "attribute vec3 vertex;\n"
    "attribute vec4 color;\n"
    "varying vec4 v_color;\n"
    "uniform mat4 projectionMatrix;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projectionMatrix * vec4(vertex,1.0);\n"
    "    v_color = color;\n"
    "}";
const char fragment_shader_source[] =
    "varying " PRECISION "vec4 v_color;\n"
    "varying " PRECISION "vec2 v_texCoord;\n"
    "uniform sampler2D tex0;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = texture2D(tex0, v_texCoord) * v_color;\n"
    "}";

void System::init()
{
    Shader vertex_shader, fragment_shader;
    geLog("Creating default programs");


    vertex_shader.init(GL_VERTEX_SHADER);
    vertex_shader.compile(vertex_shader_source);

    fragment_shader.init(GL_FRAGMENT_SHADER);
    fragment_shader.compile(fragment_shader_source);
}

}
}