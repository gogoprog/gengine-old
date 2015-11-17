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

void IndexBuffer::init(const uint count, const bool use_as_stream)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

    #ifndef EMSCRIPTEN
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort) * count, nullptr, use_as_stream ? GL_STREAM_DRAW : GL_STATIC_DRAW);
    #else
        streamUsage = use_as_stream;
        dataCount = count;
        data = new ushort[count];
    #endif
}

void IndexBuffer::finalize()
{
    glDeleteBuffers(1, &id);

    #ifdef EMSCRIPTEN
        delete []data;
    #endif
}

void IndexBuffer::setData(const ushort *indices, const uint count, const bool stream)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort) * count, indices, stream ? GL_STREAM_DRAW : GL_STATIC_DRAW);
}

ushort *IndexBuffer::map()
{
    #ifndef EMSCRIPTEN
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

        return reinterpret_cast<ushort *>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY_ARB));
    #else
        return data;
    #endif
}

void IndexBuffer::unMap()
{
    #ifndef EMSCRIPTEN
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    #else
        setData(data, dataCount, streamUsage);
    #endif
}


void IndexBuffer::draw(const uint count)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, 0);
}

}
}
