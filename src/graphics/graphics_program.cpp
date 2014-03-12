#include "graphics_program.h"

#include "debug.h"
#include "graphics_opengl.h"
#include "graphics_shader.h"

namespace gengine
{
namespace graphics
{

void Program::init()
{
    id = glCreateProgram();
}

void Program::attachShader(const Shader & shader)
{
    glAttachShader(id, shader.getId());
    GL_CHECK();
}

void Program::link()
{
    glLinkProgram(id);
    GL_CHECK();
}

}
}
