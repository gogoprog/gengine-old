#include "graphics_text.h"

#include "graphics_renderer.h"
#include "core.h"

namespace gengine
{
namespace graphics
{

Text::Text()
    :
    Object()
{
}

Renderer::Type Text::getRenderType()
{
    return Renderer::Type::TEXT;
}

void Text::update()
{
    if(font)
    {
        SDL_Color color = {1, 0, 0};

        if(surface)
        {
            SDL_FreeSurface(surface);
        }

        if(texture)
        {
            SDL_DestroyTexture(texture);
        }

        surface = TTF_RenderText_Solid(font->getTtfFont(), text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(core::getMainWindow().getSdlRenderer(), surface);
    }
}

}
}
