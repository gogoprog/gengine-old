#pragma once

#include "primitives.h"
#include "graphics_sprite.h"
#include "pointer.h"

namespace gengine
{
namespace graphics
{

class SpriteGroup : public Object
{
friend class Renderer;

public:
    SpriteGroup();
    virtual ~SpriteGroup();

    virtual Renderer::Type getRenderType() override;

    Array<Pointer<Sprite>> & getSprites() { return sprites; }

    void setActiveCount(const uint count)
    {
        activeCount = count;
    }

private:
    Array<Pointer<Sprite>>
        sprites;
    uint
        activeCount;
};

}
}
