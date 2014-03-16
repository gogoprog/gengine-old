#pragma once

#include "primitives.h"

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

    uint getId() const { return id; }

private:
    uint id;
    uint width, height;
};

}
}
