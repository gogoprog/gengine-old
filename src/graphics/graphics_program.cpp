#include "graphics_program.h"

#include "debug.h"
#include "memory.h"
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
    GLint status;

    glLinkProgram(id);

    GL_CHECK();

    glGetProgramiv(id, GL_LINK_STATUS, &status);

    if(!status )
    {
        GLchar log[2048];
        GLsizei length;

        memset(log, 0, 2048);

        glGetProgramInfoLog(id, 2048, &length, log);

        if(length > 0)
        {
            geLog("Error while linking program");
            puts(log);
        }
    }
}

}
}
