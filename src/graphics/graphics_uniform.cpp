#include "graphics_uniform.h"

#include "graphics_program.h"
#include "graphics_opengl.h"
#include "graphics_texture.h"
#include "matrix3.h"
#include "vector4.h"
#include "vector2.h"

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

void Uniform::apply(const Vector2 & vector2)
{
    glUniform2fv(location, 1, reinterpret_cast<const float *>(&vector2));
}

void Uniform::apply(const Array<Vector2> & vector2_table)
{
    glUniform2fv(location, vector2_table.getSize(), reinterpret_cast<const float *>(&vector2_table[0]));
}

void Uniform::apply(const Array<Vector4> & vector4_table)
{
    glUniform4fv(location, vector4_table.getSize(), reinterpret_cast<const float *>(&vector4_table[0]));
}

void Uniform::apply(const Array<float> & float_table)
{
    glUniform1fv(location, float_table.getSize(), reinterpret_cast<const float *>(&float_table[0]));
}

void Uniform::apply(const int value)
{
    glUniform1i(location, value);
}

}
}
