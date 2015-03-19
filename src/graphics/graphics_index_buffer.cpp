#include "graphics_index_buffer.h"

#include "graphics_opengl.h"

namespace gengine
{
namespace graphics
{

IndexBuffer::IndexBuffer()
    :
    id(GL_NULL_ID)
{
}

IndexBuffer::~IndexBuffer()
{
    if(id != GL_NULL_ID)
    {
        glDeleteBuffers(1, &id);
    }
}

void IndexBuffer::init()
{
    glGenBuffers(1, &id);
}

void IndexBuffer::finalize()
{
    glDeleteBuffers(1, &id);
}

void IndexBuffer::setData(const ushort * indices, const uint count, const bool stream)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort) * count, indices, stream ? GL_STREAM_DRAW : GL_STATIC_DRAW);
}

void IndexBuffer::draw(const uint count)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, 0);
}

}
}
