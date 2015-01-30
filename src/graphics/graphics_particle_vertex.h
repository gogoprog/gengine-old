#pragma once

#include "primitives.h"

namespace gengine
{
namespace graphics
{

struct ParticleVertex
{
    Vector2
        position,
        extent;
    Vector4
        color;
    float
        rotation;
    float
        index;

    static void enableAttributes()
    {
        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_POSITION);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_EXTENT);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_EXTENT, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + 8);

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_COLOR);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + 16);

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_ROTATION);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_ROTATION, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + 32);

        glEnableVertexAttribArray(Program::ATTRIBUTE_LOCATION_INDEX);
        glVertexAttribPointer(Program::ATTRIBUTE_LOCATION_INDEX, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + 36);
    }
};

}
}
