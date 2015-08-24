#pragma once

#include "script.h"

namespace gengine
{
namespace math
{

struct Vector4
{
    Vector4() = default;
    Vector4(const float _x, const float _y, const float _z, const float _w);

    Vector4 & operator*=(const float value);
    Vector4 & operator/=(const Vector4 & other);
    Vector4 & operator-=(const Vector4 & other);
    Vector4 & operator+=(const Vector4 & other);
    Vector4 & operator*=(const Vector4 & other);

    float x,y,z,w;

    static Vector4
        zero,
        one;

    static SCRIPT_REGISTERER();
    static void fill(lua_State * state, Vector4 & result, int position = -1);
    static void fillTableSafe(lua_State * state, Vector4 & result, const char * name, int position = -1, const Vector4 & default_value = Vector4::zero);
};

Vector4 operator*(const Vector4 & vector, const float multiplier);
Vector4 operator-(const Vector4 & a, const Vector4 & b);
Vector4 operator+(const Vector4 & a, const Vector4 & b);
Vector4 operator*(const Vector4 & a, const Vector4 & b);

}
}
