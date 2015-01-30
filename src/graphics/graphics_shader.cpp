#include "graphics_shader.h"

#include "debug.h"
#include "memory.h"
#include "graphics_opengl.h"

namespace gengine
{
namespace graphics
{

void Shader::init(const GLenum _type)
{
    type = _type;
    id = glCreateShader(type);
}

void Shader::finalize()
{
    glDeleteShader(id);
}

void Shader::compile(const char * source)
{
    GLint status;

    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if(!status)
    {
        GLchar log[2048];
        GLsizei length;

        memset(log, 0, 2048);

        glGetShaderInfoLog(id, 2048, &length, log);

        if(length > 0)
        {
            geDebugLog("Error while compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader :" );
            puts(log);
        }
    }
}

}
}
