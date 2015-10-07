#pragma once

#include "primitives.h"
#include "vector2.h"
#include "vector4.h"
#include "matrix3.h"
#include "graphics_object.h"
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


private:
    Pointer<SDL_Surface>
        texture;
};

}
}
