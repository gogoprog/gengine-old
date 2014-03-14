#include "graphics_program.h"

#include "debug.h"
#include "memory.h"
#include "graphics_opengl.h"
#include "graphics_shader.h"
#include "graphics_uniform.h"

namespace gengine
{
namespace graphics
{

void Program::init()
{
    id = glCreateProgram();
    glBindAttribLocation(id,ATTRIBUTE_LOCATION_POSITION,"position");
    glBindAttribLocation(id,ATTRIBUTE_LOCATION_COLOR,"color");
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

    GL_CHECK();
}

void Program::use()
{
    glUseProgram(id);
}

void Program::setUniformValue(const Uniform & uniform, const Matrix3 & matrix)
{
    glUniformMatrix3fv(uniform.location, 1, GL_FALSE, reinterpret_cast<const float *>(&matrix));
}

}
}
