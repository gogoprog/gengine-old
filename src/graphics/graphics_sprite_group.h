#pragma once

#include "primitives.h"
#include "graphics_sprite.h"

namespace gengine
{
namespace graphics
{

class SpriteGroup : public Object
{
friend class Renderer;

public:
    SpriteGroup();

    virtual Renderer::Type getRenderType() override;

private:
    Array<Sprite>
        sprites;
};

}
}
