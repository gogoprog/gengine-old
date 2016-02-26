#pragma once

#include "script.h"
#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Math/Vector3.h>

namespace gengine
{
namespace math
{

typedef Urho3D::Vector2
    Vector2;
typedef Urho3D::Vector3
    Vector3;

SCRIPT_REGISTERER();

template<class T>
T getLerp(const T & first, const T & second, const float factor)
{
    return first * ( 1.0f - factor ) + second * factor;
}

const float pi = 3.14159265358979323846264338327950288419716939937510f;

float getClosestAngle(const float angle, const float other_angle);

}

SCRIPT_TYPE(math::Vector2, "Vector2")
SCRIPT_TYPE(math::Vector3, "Vector3")

}
