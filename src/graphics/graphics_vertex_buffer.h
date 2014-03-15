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

    void init()
    {
        glGenBuffers(1, &id);
    }

    void finalize()
    {
        glDeleteBuffers(1, &id);
    }

    void setData(const VERTEX * vertices, const uint count)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * count, vertices, GL_STATIC_DRAW);
    }

    void apply()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_POSITION);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX), 0);

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_COLOR);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(VERTEX), (char*)0 + 8);

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_TEXCOORDS);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX), (char*)0 + 8 + 16);
    }

private:
    uint id;
};

}
}
