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


}
}
