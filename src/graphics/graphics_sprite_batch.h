#pragma once

#include "primitives.h"
#include "graphics_object.h"
#include "graphics_vertex.h"
#include "vector2.h"

namespace gengine
{
namespace graphics
{

class Atlas;

class SpriteBatch : public Object
{
friend class Renderer;

public:
    SpriteBatch();

    virtual Renderer::Type getRenderType() override;

    void setTexture(const Texture & _texture)
    {
        texture = & _texture;
    }

    void setScale(const Vector2 & _scale)
    {
        scale = _scale;
    }

    const uint getVertexCount() const { return vertexCount; }

    void init(const uint size);
    void addItem(const Atlas *atlas, const int index, const Vector2 & position, const Vector2 & extent);
    void addItem(const Atlas *atlas, const int index, const Vector2 & position);
    Vertex *getAddedVertices(const uint count);

    void lock();
    void unlock();

private:
    VertexBuffer<Vertex>
        vertexBuffer;
    Vertex
        * vertices;
    uint
        vertexCount;
    Pointer<const Texture>
        texture;
    Vector2
        scale;
};

}
}
