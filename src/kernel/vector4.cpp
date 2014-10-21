#include "vector4.h"

namespace gengine
{

Vector4::Vector4(const float _x, const float _y, const float _z, const float _w)
    :
    x(_x),
    y(_y),
    z(_z),
    w(_w)
{
}

Vector4
    Vector4::zero(0.0f, 0.0f, 0.0f, 0.0f),
    Vector4::one(1.0f, 1.0f, 1.0f, 1.0f);
}