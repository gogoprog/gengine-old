#include "vector2.h"

namespace gengine
{

Vector2::Vector2(const float _x, const float _y)
    :
    x(_x),
    y(_y)
{
}

Vector2 Vector2::zero(0.0f, 0.0f);

}