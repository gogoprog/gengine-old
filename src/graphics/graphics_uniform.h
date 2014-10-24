#pragma once

#include "primitives.h"

namespace gengine
{

class Matrix3;
struct Vector4;
struct Vector2;

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

    uint getLocation() const { return location; }

private:
    uint
        location;
};

}
}
