#pragma once

#include "primitives.h"
#include "vector4.h"

namespace gengine
{
namespace graphics
{

struct Vertex
{
    math::Vector2
        position,
        texCoords;
    math::Vector4
        color;

    static void enableAttributes()
    {
        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_POSITION);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_TEXCOORDS);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_COLOR);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    }
};

}
}
