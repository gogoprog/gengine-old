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
friend class Text;

public:
    Font() = default;
    ~Font();

    void init();
    void finalize();
    bool setFromFile(const char * filename, const int size);

    inline TTF_Font *getTtfFont() const
    {
        return & * font;
    }

private:
    Pointer<TTF_Font>
        font;
};

}
}
