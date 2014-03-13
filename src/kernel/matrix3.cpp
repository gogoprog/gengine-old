#include "matrix3.h"

namespace gengine
{

Matrix3::Matrix3()
{
}

void Matrix3::setIdentity()
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

void Matrix3::setTranslation(const float x, const float y)
{
    get(2,0) = x;
    get(2,1) = y;
}

}
