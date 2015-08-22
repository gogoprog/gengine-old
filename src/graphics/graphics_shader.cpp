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

void Shader::compile(const char * source, const char * name)
{
    GLint status;
    const char *sources[3];

    #ifdef EMSCRIPTEN
        sources[0] = "#define WEBGL\n";
    #else
        sources[0] = "";
    #endif

    sources[1] = source;

    glShaderSource(id, 2, sources, nullptr);
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
            geLog("Error while compiling " << name << " " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader :" );
            puts(log);
        }
    }
}

}
}
