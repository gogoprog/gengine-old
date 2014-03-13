#include "graphics_index_buffer.h"

#include "graphics_opengl.h"

namespace gengine
{
namespace graphics
{

IndexBuffer::IndexBuffer()
    :
    id(0xffffffff)
{
}

IndexBuffer::~IndexBuffer()
{
    if(id != 0xffffffff)
    {
        glDeleteBuffers(1, &id);
    }
}

void IndexBuffer::init()
{
    glGenBuffers(1, &id);
}

void IndexBuffer::setData(const ushort * indices, const uint _count)
{
    count = _count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort) * count, indices, GL_STATIC_DRAW);
}

void IndexBuffer::draw(const uint _count)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_SHORT, 0);
}

void IndexBuffer::draw()
{
    draw(count);
}

}
}
