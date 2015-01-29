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

    void setAtlas(const Atlas & _atlas)
    {
        atlas = & _atlas;
    }

    const uint getItemCount() const { return itemCount; }

    void init(const uint size);
    void addItem(const int index, const Vector2 & position, const Vector2 & extent);
    void addItem(const int index, const Vector2 & position);
    void reserve(const int size);

    void lock();
    void unlock();

private:
    VertexBuffer<Vertex>
        vertexBuffer;
    Vertex
        * vertices;
    uint
        itemCount,
        maximumItemCount;
    const Atlas
        * atlas;
};

}
}
