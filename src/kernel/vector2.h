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

    void set(const float _x, const float _y);
    void normalize();

    union
    {
        float x;
        float u;
    };
    union
    {
        float y;
        float v;
    };

    static Vector2
        zero,
        one;

    static SCRIPT_REGISTERER();

    static void push(lua_State * state, const Vector2 & value);
    static void replace(lua_State * state, const Vector2 & value);

    static void fill(lua_State * state, Vector2 & result, int position = -1);
    static void fillTableSafe(lua_State * state, Vector2 & result, const char * name, int position = -1, const Vector2 & default_value = Vector2::zero);

    static float getLength(const Vector2 & a);
    static float getSquareLength(const Vector2 & a);
    static float getDistance(const Vector2 & a, const Vector2 & b);
    static float getSquareDistance(const Vector2 & a, const Vector2 & b);
    static float getAngle(const Vector2 & a, const Vector2 & b);

private:

    static int
        metaTableRef;
};

Vector2 operator*(const Vector2 & vector, const float multiplier);
Vector2 operator-(const Vector2 & a, const Vector2 & b);
Vector2 operator+(const Vector2 & a, const Vector2 & b);

}
