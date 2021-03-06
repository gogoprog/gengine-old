#include "graphics_text.h"

#include "graphics_renderer.h"
#include "core.h"
#include "debug.h"

namespace gengine
{
namespace graphics
{

Text::Text()
    :
    Object()
{
}

Text::~Text()
{
    if(surface)
    {
        SDL_FreeSurface(surface);
        texture.finalize();
    }
}

Renderer::Type Text::getRenderType()
{
    return Renderer::Type::TEXT;
}

void Text::update()
{
    if(font && text.size())
    {
        static SDL_Color color = {255, 255, 255, 0};

        if(surface)
        {
            SDL_FreeSurface(surface);
            texture.finalize();
        }

        surface = TTF_RenderText_Blended(font->getTtfFont(), text.c_str(), color);

        if(surface)
        {
            texture.init();
            texture.setFromSdlSurface(* surface);
        }
    }
}

void Text::scale(const math::Vector2 & scaling)
{
    extent.x = surface->w * scaling.x;
    extent.y = surface->h * scaling.y;
}


}
}
