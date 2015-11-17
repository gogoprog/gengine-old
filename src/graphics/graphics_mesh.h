#pragma once

#include "primitives.h"
#include "graphics_object.h"
#include "graphics_vertex_buffer.h"
#include "graphics_index_buffer.h"
#include "vector2.h"

namespace gengine
{
namespace graphics
{

template<typename VERTEX>
class Mesh : public Object
{
friend class Renderer;

public:
    Mesh()
        :
        Object(),
        vertexCount(0),
        indexCount(0),
        scale(math::Vector2::one)
    {
    }

    virtual Renderer::Type getRenderType() override
    {
        return Renderer::Type::MESH;
    }

    void setTexture(const Texture & _texture)
    {
        texture = & _texture;
    }

    void setScale(const Vector2 & _scale)
    {
        scale = _scale;
    }

    void init(const uint maximum_vertex_count, const uint maximum_index_count)
    {
        vertexBuffer.init(maximum_vertex_count, true);
        indexBuffer.init(maximum_index_count, true);
    }

    VertexBuffer<VERTEX> & getVertexBuffer()
    {
        return vertexBuffer;
    }

    IndexBuffer & getIndexBuffer()
    {
        return indexBuffer;
    }

    void setVertexCount(const uint count)
    {
        vertexCount = count;
    }

    void setIndexCount(const uint count)
    {
        indexCount = count;
    }

private:
    VertexBuffer<VERTEX>
        vertexBuffer;
    IndexBuffer
        indexBuffer;
    uint
        vertexCount,
        indexCount;
    Pointer<const Texture>
        texture;
    Vector2
        scale;
};

}
}
