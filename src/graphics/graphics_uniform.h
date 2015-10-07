#pragma once

#include "primitives.h"
#include "array.h"
struct SDL_Texture;

namespace gengine
{

namespace math {
    class Matrix3;
    struct Vector4;
    struct Vector2;
}

using namespace math;

namespace graphics
{

class Program;
class Texture;

class Uniform
{
friend class Program;

public:
    void init(const Program & program, const char * name);
    void apply(const Matrix3 & matrix);
    void apply(const Texture & texture);
    void apply(const Vector4 & vector4);
    void apply(const Vector2 & vector2);
    void apply(const Array<Vector2> & vector2_table);
    void apply(const Array<Vector4> & vector4_table);
    void apply(const Array<float> & float_table);
    void apply(const int value);
    void apply(SDL_Texture & sdl_texture);

    uint getLocation() const { return location; }

private:
    uint
        location;
};

}
}
