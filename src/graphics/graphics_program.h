#pragma once

#include "primitives.h"
#include "matrix3.h"

namespace gengine
{
namespace graphics
{

class Shader;
class Uniform;
class Texture;

class Program
{
public:
    enum AttributeLocation
    {
        ATTRIBUTE_LOCATION_POSITION,
        ATTRIBUTE_LOCATION_EXTENT,
        ATTRIBUTE_LOCATION_TEXCOORDS,
        ATTRIBUTE_LOCATION_ROTATION,
        ATTRIBUTE_LOCATION_INDEX,
        ATTRIBUTE_LOCATION_LIFE
    };

    void init();
    void finalize();
    void attachShader(const Shader & shader);
    void link();
    void use();
    void setUniformValue(const Uniform & uniform, const Matrix3 & matrix);
    void setUniformValue(const Uniform & uniform, const Texture & texture);

    uint getId() const { return id; }

private:
    uint
        id;
};

}
}
