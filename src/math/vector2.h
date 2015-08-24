#pragma once

#include "script.h"
#include "script_binder.h"

namespace gengine
{
namespace math
{

struct Vector2
{
    friend class script::Binder<Vector2>;

    Vector2() = default;
    Vector2(const float _x, const float _y);

    Vector2 & operator*=(const float value);
    Vector2 & operator/=(const Vector2 & other);
    Vector2 & operator-=(const Vector2 & other);
    Vector2 & operator+=(const Vector2 & other);
    Vector2 & operator*=(const Vector2 & other);

    void set(const float _x, const float _y);
    void normalize();
    void rotate(const float angle);

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

    static float getLength(const Vector2 & a);
    static float getSquareLength(const Vector2 & a);
    static float getDistance(const Vector2 & a, const Vector2 & b);
    static float getSquareDistance(const Vector2 & a, const Vector2 & b);
    static float getAngle(const Vector2 & a, const Vector2 & b);
    static Vector2 getRotated(Vector2 v, const float angle);

private:

    static int
        metaTableRef;
};

Vector2 operator*(const Vector2 & vector, const float multiplier);
Vector2 operator-(const Vector2 & a, const Vector2 & b);
Vector2 operator+(const Vector2 & a, const Vector2 & b);
Vector2 operator*(const Vector2 & a, const Vector2 & b);

}

namespace script {
template<>
class Binder<math::Vector2>
{
public:
    static void push(script::State state, const math::Vector2 & value)
    {
        lua_newtable(state);
        lua_pushnumber(state, value.x);
        lua_setfield(state, -2, "x");

        lua_pushnumber(state, value.y);
        lua_setfield(state, -2, "y");

        lua_rawgeti(state, LUA_REGISTRYINDEX, math::Vector2::metaTableRef);
        lua_setmetatable(state, -2);
    }

    static void update(script::State state, const math::Vector2 & value)
    {
        lua_pushnumber(state, value.x);
        lua_setfield(state, -2, "x");

        lua_pushnumber(state, value.y);
        lua_setfield(state, -2, "y");
    }

    static void get(script::State state, math::Vector2 & result, int position = -1)
    {
        lua_getfield(state, position, "x");
        result.x = lua_tonumber(state, -1);
        lua_pop(state, 1);

        lua_getfield(state, position, "y");
        result.y = lua_tonumber(state, -1);
        lua_pop(state, 1);
    }
};
}

}
