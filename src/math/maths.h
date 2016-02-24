#pragma once

#include "script.h"
#include "vector2.h"

namespace gengine
{
namespace math
{

SCRIPT_REGISTERER();

template<class T>
T getLerp(const T & first, const T & second, const float factor)
{
    return first * ( 1.0f - factor ) + second * factor;
}

const float pi = 3.14159265358979323846264338327950288419716939937510f;

float getClosestAngle(const float angle, const float other_angle);

}
}
