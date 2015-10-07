#include "graphics_font.h"

#include "debug.h"

namespace gengine
{
namespace graphics
{

Font::~Font()
{
    if(font)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void Font::init()
{
}

void Font::finalize()
{
}

bool Font::setFromFile(const char * filename, const int size)
{
    geDebugLogN("graphics::Font::setFromFile \"" << filename << "\"(" << size << ")" << " ... ");

    font = TTF_OpenFont(filename, size);

    if(font)
    {
        geDebugRawLog("Ok.");
        return true;
    }

    geDebugRawLog("Failed! " << TTF_GetError());

    return false;
}

}
}
