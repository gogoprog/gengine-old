#pragma once

#include "primitives.h"
#include "matrix3.h"
#include "map.h"

namespace gengine
{
namespace graphics
{

class Shader;

class Program
{
public:
    enum AttributeLocation
    {
        ATTRIBUTE_LOCATION_POSITION,
        ATTRIBUTE_LOCATION_COLOR
    };

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
