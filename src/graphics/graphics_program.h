#pragma once

#include "primitives.h"
#include "matrix3.h"

namespace gengine
{
namespace graphics
{

class Shader;

class Program
{
public:
    void init();
    void attachShader(const Shader & shader);
    void link();
    void use();
    void setUniform(const uint location, const Matrix3 & matrix);

    uint getId() const { return id; }

private:
    uint id;
};

}
}
