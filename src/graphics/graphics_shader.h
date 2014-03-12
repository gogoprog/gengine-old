#pragma once

#include "primitives.h"
#include "graphics_opengl.h"

namespace gengine
{
namespace graphics
{

class Shader
{
public:
    void init(const GLenum _type);
    void compile(const char *source);

private:
    uint id;
    GLenum type;
};

}
}
