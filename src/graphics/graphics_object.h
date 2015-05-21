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

class Object
{
friend class Renderer;
friend class World;

public:
    Object():
        position(Vector2(- 1000000.0f, - 1000000.0f)),
        color(1.0f, 1.0f, 1.0f, 1.0f),
        rotation(0.0f),
        layer(0)
    {
    }

    virtual ~Object() = default;

    virtual Renderer::Type getRenderType() = 0;

    const Vector2 & getPosition() const { return position; }
    Vector2 & getPosition() { return position; }
    const Vector4 & getColor() const { return color; }
    Vector4 & getColor() { return color; }

    void setPosition(const Vector2 & _position) { position = _position; }
    void setColor(const Vector4 & _color) { color = _color; }
    void setColorAlpha(const float alpha) { color.w = alpha; }
    void setRotation(const float angle) { rotation = angle; }
    void setLayer(const int _layer) { layer = _layer; }

protected:
    Vector2
        position;
    Vector4
        color;
    float
        rotation;
    int
        layer;
};

}
}
