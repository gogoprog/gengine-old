#include "graphics_uniform.h"

#include "graphics_program.h"
#include "graphics_opengl.h"
#include "graphics_texture.h"
#include "matrix3.h"
#include "vector4.h"

namespace gengine
{
namespace graphics
{

void Uniform::init(const Program & program, const char * name)
{
    location = glGetUniformLocation(program.getId(), name);
}

void Uniform::apply(const Matrix3 & matrix)
{
    glUniformMatrix3fv(location, 1, GL_FALSE, reinterpret_cast<const float *>(&matrix));
}

void Uniform::apply(const Texture & texture)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getId());
    glUniform1i(location, 0);
}

void Uniform::apply(const Vector4 & vector4)
{
    glUniform4fv(location, 1, reinterpret_cast<const float *>(&vector4));
}

}
}
