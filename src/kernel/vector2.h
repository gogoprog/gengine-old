#pragma once

namespace gengine
{

struct Vector2
{
    Vector2() = default;
    Vector2(const float _x, const float _y);

    float x,y;

    static Vector2 zero;
};

}