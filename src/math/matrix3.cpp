#include "matrix3.h"

#include "core_sdl.h"
#include <math.h>

namespace gengine
{
namespace math
{

void Matrix3::initIdentity()
{
    get(0,0) = 1.0f;
    get(1,0) = 0.0f;
    get(2,0) = 0.0f;

    get(0,1) = 0.0f;
    get(1,1) = 1.0f;
    get(2,1) = 0.0f;

    get(0,2) = 0.0f;
    get(1,2) = 0.0f;
    get(2,2) = 1.0f;
}

void Matrix3::initProjection(const Vector2 & extent, const Vector2 & translation)
{
    get(0,0) = 2.0f / extent.x;
    get(1,0) = 0.0f;
    get(2,0) = 0.0f;

    get(0,1) = 0.0f;
    get(1,1) = 2.0f / extent.y,
    get(2,1) = 0.0f;

    get(0,2) = - get(0,0) * translation.x;
    get(1,2) = - get(1,1) * translation.y;
    get(2,2) = 1.0f;
}

void Matrix3::setTranslation(const Vector2 & translation)
{
    get(2,0) = translation.x;
    get(2,1) = translation.y;
}

void Matrix3::setRotation(const float angle)
{
    float sin = sinf(angle);
    float cos = cosf(angle);

    get(0,0) = cos;
    get(1,0) = -sin;
    get(0,1) = sin;
    get(1,1) = cos;
}

void Matrix3::preScale(const Vector2 & s)
{
    get(0,0) *= s.x;
    get(0,1) *= s.x;

    get(1,0) *= s.y;
    get(1,1) *= s.y;
}

void Matrix3::scale(const Vector2 & s)
{
    get(0,0) *= s.x;
    get(1,0) *= s.x;

    get(0,1) *= s.y;
    get(1,1) *= s.y;
}

}
}
