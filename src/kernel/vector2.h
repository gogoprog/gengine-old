#pragma once

namespace gengine
{

struct Vector2
{
    Vector2() = default;
    Vector2(const float _x, const float _y);

    Vector2 & operator/=(const Vector2 & other);
    Vector2 & operator-=(const Vector2 & other);
    Vector2 & operator+=(const Vector2 & other);

    float x,y;

    static Vector2
        zero,
        one;
};

Vector2 operator*(const Vector2 & vector, const float multiplier);

}
