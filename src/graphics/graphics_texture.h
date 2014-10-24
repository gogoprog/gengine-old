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
    bool setFromFile(const char * filename);

    uint getId() const { return id; }

private:
    uint
        id,
        width,
        height;
};

}
}
