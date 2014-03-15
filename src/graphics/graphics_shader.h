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
    uint getId() const { return id; }
    void init(const GLenum _type);
    void finalize();
    void compile(const char *source);

private:
    uint id;
    GLenum type;
};

}
}
