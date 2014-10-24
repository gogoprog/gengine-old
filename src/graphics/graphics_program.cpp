#include "graphics_program.h"

#include "debug.h"
#include "memory.h"
#include "graphics_opengl.h"
#include "graphics_shader.h"
#include "graphics_uniform.h"
#include "graphics_texture.h"

namespace gengine
{
namespace graphics
{

void Program::init()
{
    id = glCreateProgram();
    glBindAttribLocation(id,ATTRIBUTE_LOCATION_POSITION,"position");
    glBindAttribLocation(id,ATTRIBUTE_LOCATION_COLOR,"color");
    glBindAttribLocation(id,ATTRIBUTE_LOCATION_TEXCOORDS,"texCoords");
}

void Program::finalize()
{
    glDeleteProgram(id);
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
            geDebugLog("Error while linking program");
            puts(log);
        }
    }

    GL_CHECK();
}

void Program::use()
{
    glUseProgram(id);
}


}
}
