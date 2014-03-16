#include "matrix3.h"

#include "core_sdl.h"
#include <math.h>

namespace gengine
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

void Matrix3::initProjection(const float width, const float height, const float tx, const float ty)
{
    get(0,0) = 2.0f / width;
    get(1,0) = 0.0f;
    get(2,0) = 0.0f;

    get(0,1) = 0.0f;
    get(1,1) = 2.0f / height,
    get(2,1) = 0.0f;

    get(0,2) = - get(0,0) * tx;
    get(1,2) = - get(1,1) * ty;
    get(2,2) = 1.0f;
}

void Matrix3::setTranslation(const float x, const float y)
{
    get(2,0) = x;
    get(2,1) = y;
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

void Matrix3::preScale(const float sx, const float sy)
{
    get(0,0) *= sx;
    get(0,1) *= sx;

    get(1,0) *= sy;
    get(1,1) *= sy;
}

void Matrix3::scale(const float sx, const float sy)
{
    get(0,0) *= sx;
    get(1,0) *= sx;

    get(0,1) *= sy;
    get(1,1) *= sy;
}

}
