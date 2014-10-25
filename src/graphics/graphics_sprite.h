#pragma once

#include "primitives.h"
#include "vector2.h"
#include "vector4.h"
#include "matrix3.h"
#include "graphics_renderer.h"

namespace gengine
{
namespace graphics
{

class Texture;

class Sprite
{
friend class Renderer;
friend class World;

public:
    Sprite();

    const Vector2 & getPosition() const { return position; }
    Vector2 & getPosition() { return position; }
    const Vector2 & getExtent() const { return extent; }
    Vector2 & getExtent() { return extent; }
    const Vector2 & getUvScale() const { return uvScale; }
    Vector2 & getUvScale() { return uvScale; }
    const Vector2 & getUvOffset() const { return uvOffset; }
    Vector2 & getUvOffset() { return uvOffset; }
    const Vector4 & getColor() const { return color; }
    Vector4 & getColor() { return color; }

    void setPosition(const Vector2 & _position) { position = _position; }
    void setExtent(const Vector2 & _extent) { extent = _extent; }
    void setUvScale(const Vector2 & uv_scale) { uvScale = uv_scale; }
    void setUvOffset(const Vector2 & uv_offset) { uvOffset = uv_offset; }
    void setColor(const Vector4 & _color) { color = _color; }
    void setColorAlpha(const float alpha) { color.w = alpha; }
    void setRotation(const float angle) { rotation = angle; }
    void setTexture(const Texture & _texture) { texture = & _texture; }
    void setLayer(const int _layer) { layer = _layer; }

private:
    Vector2
        position,
        extent,
        uvScale,
        uvOffset;
    Vector4
        color;
    float
        rotation;
    const Texture
        * texture;
    int
        layer;
    static Renderer::Type
        renderType;
};

}
}
