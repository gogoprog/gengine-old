#include "graphics_uniform.h"

#include "graphics_program.h"
#include "graphics_opengl.h"

namespace gengine
{
namespace graphics
{

void Uniform::init(const Program & program, const char * name)
{
    location = glGetUniformLocation(program.getId(), name);
}

}
}
