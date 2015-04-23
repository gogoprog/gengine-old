#pragma once

#include "primitives.h"

namespace gengine
{
namespace graphics
{

struct Vertex
{
    Vector2
        position,
        texCoords;

    static void enableAttributes()
    {
        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_POSITION);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_TEXCOORDS);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    }
};

}
}
