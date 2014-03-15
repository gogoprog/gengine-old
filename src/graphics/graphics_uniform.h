#pragma once

#include "primitives.h"

namespace gengine
{

class Matrix3;

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

    uint getLocation() const { return location; }

private:
    uint location;
};

}
}
