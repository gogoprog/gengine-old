#pragma once

#include "primitives.h"
#include "pointer.h"
#include "core_sdl.h"

namespace gengine
{
namespace graphics
{

class Font
{
friend class Renderer;

public:
    Font() = default;
    ~Font();

    void init();
    void finalize();
    bool setFromFile(const char * filename);

private:
    Pointer<TTF_Font>
        font;
};

}
}
