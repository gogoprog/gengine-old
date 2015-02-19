#pragma once

#include "primitives.h"
#include "graphics_opengl.h"
#include "graphics_program.h"

namespace gengine
{
namespace graphics
{

template<typename VERTEX>
class VertexBuffer
{
public:
    VertexBuffer()
        :
        id(GL_NULL_ID)
    {
    }

    ~VertexBuffer()
    {
        if(id != GL_NULL_ID)
        {
            glDeleteBuffers(1, &id);
        }
    }

    void init(const uint count, const bool use_as_stream)
    {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);

        #ifndef EMSCRIPTEN
            glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * count, nullptr, use_as_stream ? GL_STREAM_DRAW : GL_STATIC_DRAW);
        #else
            streamUsage = use_as_stream;
            dataCount = count;
        #endif
    }

    void finalize()
    {
        glDeleteBuffers(1, &id);
    }

    void apply()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);

        VERTEX::enableAttributes();
    }

    VERTEX * map()
    {
        #ifndef EMSCRIPTEN
            glBindBuffer(GL_ARRAY_BUFFER, id);

            return reinterpret_cast<VERTEX *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY_ARB));
        #else
            return data;
        #endif
    }

    void unMap()
    {
        #ifndef EMSCRIPTEN
            glUnmapBuffer(GL_ARRAY_BUFFER);
        #else
            glBindBuffer(GL_ARRAY_BUFFER, id);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * dataCount, data, streamUsage ? GL_STREAM_DRAW : GL_STATIC_DRAW);
        #endif
    }

private:
    uint
        id;
    #ifdef EMSCRIPTEN
        VERTEX
            data[10240];
        uint
            dataCount;
        bool
            streamUsage;
    #endif
};

}
}
