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
    uint
        index;
};

}
}
