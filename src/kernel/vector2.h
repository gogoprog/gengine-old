#pragma once

#include "script.h"

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

    static SCRIPT_REGISTERER();

    static void fill(lua_State * state, Vector2 & result, int position = -1);
    static void fillTableSafe(lua_State * state, Vector2 & result, const char * name, int position = -1, const Vector2 & default_value = Vector2::zero);
};

Vector2 operator*(const Vector2 & vector, const float multiplier);

}
