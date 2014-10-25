#pragma once

#include "primitives.h"
#include "vector2.h"
#include "vector4.h"
#include "matrix3.h"
#include "graphics_object.h"

namespace gengine
{
namespace graphics
{

class Texture;

class Sprite : public Object
{
friend class Renderer;
friend class World;

public:
    Sprite();

    virtual Renderer::Type getRenderType() override;

    const Vector2 & getExtent() const { return extent; }
    Vector2 & getExtent() { return extent; }
    const Vector2 & getUvScale() const { return uvScale; }
    Vector2 & getUvScale() { return uvScale; }
    const Vector2 & getUvOffset() const { return uvOffset; }
    Vector2 & getUvOffset() { return uvOffset; }

    void setExtent(const Vector2 & _extent) { extent = _extent; }
    void setUvScale(const Vector2 & uv_scale) { uvScale = uv_scale; }
    void setUvOffset(const Vector2 & uv_offset) { uvOffset = uv_offset; }

private:
    Vector2
        extent,
        uvScale,
        uvOffset;
};

}
}
