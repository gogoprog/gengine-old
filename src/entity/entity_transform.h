#pragma once

#include "primitives.h"
#include "array.h"
#include "vector2.h"
#include "script.h"
#include "debug.h"

namespace gengine
{
namespace entity
{

struct Transform
{
    math::Vector2
        position;
    float
        rotation;
};

}
}
