#pragma once

#include "primitives.h"
#include "vector2.h"
#include "vector4.h"
#include "matrix3.h"
#include "graphics_object.h"
#include "graphics_font.h"
#include "pointer.h"
struct SDL_Surface;

namespace gengine
{
namespace graphics
{

class Text : public Object
{
friend class Renderer;

public:
    Text();

    virtual Renderer::Type getRenderType() override;

    const Pointer<const Font> getFont() const { return font; }
    void setFont(const Font & _font) { font = & _font; }
    void setText(const char *text);

private:
    Pointer<SDL_Surface>
        surface;
    Pointer<const Font>
        font;
};

}
}
