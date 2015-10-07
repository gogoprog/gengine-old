#include "graphics_text.h"

#include "graphics_renderer.h"

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

void Text::setText(const char *text)
{
    SDL_Color color = {0, 0, 0};
    surface = TTF_RenderText_Blended(font->getTtfFont(), text, color);
}


}
}
