#pragma once

#include "primitives.h"
#include "core_sdl.h"

namespace gengine
{
namespace graphics
{

class Texture
{
friend class TextureManager;

public:
    Texture();
    void init();
    void finalize();
    void setFromFile(const char * filename);

private:
    uint id;
    uint width, height;
};

}
}
