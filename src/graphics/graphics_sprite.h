#pragma once

#include "primitives.h"
#include "vector2.h"
#include "matrix3.h"

namespace gengine
{
namespace graphics
{

class Texture;

class Sprite
{
friend class World;

public:
    Sprite();

    const Vector2 & getPosition() { return position; }
    const Vector2 & getExtent() { return extent; }

    void setPosition(const Vector2 & _position) { position = _position; }
    void setExtent(const Vector2 & _extent) { extent = _extent; }

    void setTexture(const Texture & _texture) { texture = & _texture; }

private:
    Vector2
        position,
        extent;
    const Texture
        * texture;
};

}
}
