#include "vector2.h"

#include <cmath>
#include <cstdlib>

namespace gengine
{

SCRIPT_FUNCTION(getLength)
{
    Vector2 a;

    Vector2::fill(state, a, 1);

    float l = Vector2::getLength(a);
    lua_pushnumber(state, l);

    return 1;
}

SCRIPT_FUNCTION(getSquareLength)
{
    Vector2 a;

    Vector2::fill(state, a, 1);

    float sl = Vector2::getSquareLength(a);
    lua_pushnumber(state, sl);

    return 1;
}

SCRIPT_FUNCTION(getDistance)
{
    Vector2 a, b;

    Vector2::fill(state, a, 1);
    Vector2::fill(state, b, 2);

    float d = Vector2::getDistance(a, b);
    lua_pushnumber(state, d);

    return 1;
}

SCRIPT_FUNCTION(getSquareDistance)
{
    Vector2 a, b;

    Vector2::fill(state, a, 1);
    Vector2::fill(state, b, 2);

    float d = Vector2::getSquareDistance(a, b);
    lua_pushnumber(state, d);

    return 1;
}

SCRIPT_FUNCTION(getAngle)
{
    Vector2 a, b;

    Vector2::fill(state, a, 1);
    Vector2::fill(state, b, 2);

    float angle = Vector2::getAngle(a, b);
    lua_pushnumber(state, angle);

    return 1;
}

SCRIPT_FUNCTION(getNormalized)
{
    Vector2 a;

    Vector2::fill(state, a, 1);

    a.normalize();

    Vector2::push(state, a);

    return 1;
}

SCRIPT_FUNCTION(getRotated)
{
    Vector2 v;
    float a;

    Vector2::fill(state, v, 1);
    a = lua_tonumber(state, 2);

    v.rotate(a);

    Vector2::push(state, v);

    return 1;
}

Vector2::Vector2(const float _x, const float _y)
    :
    x(_x),
    y(_y)
{
}

Vector2 & Vector2::operator*=(const float value)
{
    x *= value;
    y *= value;

    return * this;
}

Vector2 & Vector2::operator/=(const Vector2 & other)
{
    x /= other.x;
    y /= other.y;

    return * this;
}

Vector2 & Vector2::operator-=(const Vector2 & other)
{
    x -= other.x;
    y -= other.y;

    return * this;
}

Vector2 & Vector2::operator+=(const Vector2 & other)
{
    x += other.x;
    y += other.y;

    return * this;
}

void Vector2::set(const float _x, const float _y)
{
    x = _x;
    y = _y;
}

void Vector2::normalize()
{
    float length = getLength(*this);

    x /= length;
    y /= length;
}

void Vector2::rotate(const float angle)
{
    float c, s, nx, ny;
    c = cos(angle);
    s = sin(angle);

    nx = x * c - y * s;
    ny = x * s + y * c;

    x = nx;
    y = ny;
}

Vector2
    Vector2::zero(0.0f, 0.0f),
    Vector2::one(1.0f, 1.0f);

SCRIPT_CLASS_REGISTERER(Vector2)
{
    SCRIPT_DO(
        vector2_mt = {
            __tostring = function(t)
                return "(" .. string.format("%0.2f", t.x) .. ", " .. string.format("%0.2f", t.y) .. ")"
            end,
            __index = {
                set = function(t, x, y)
                    if type(x) == "number" then
                        t.x = x
                        t.y = y
                    elseif x.x == nil then
                        t.x = x[1]
                        t.y = x[2]
                    else
                        t.x = x.x
                        t.y = x.y
                    end
                end
            },
            __unm = function(t)
                return vector2(-t.x, -t.y)
            end,
            __add = function(a, b)
                return vector2(a.x + b.x, a.y + b.y)
            end,
            __sub = function(a, b)
                return vector2(a.x - b.x, a.y - b.y)
            end,
            __mul = function(a, b)
                return vector2(a.x * b, a.y * b)
            end,
            __div = function(a, b)
                return vector2(a.x / b, a.y / b)
            end,
            __eq = function(a, b)
                return a.x == b.x and a.y == b.y
            end
        }

        function vector2(_x, _y)
            local r = {x=_x or 0, y=_y or 0}
            setmetatable(r, vector2_mt)
            return r
        end
        );

    lua_getglobal(state, "vector2_mt");
    metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

    SCRIPT_TABLE_PUSH_FUNCTION(getLength);
    SCRIPT_TABLE_PUSH_FUNCTION(getSquareLength);
    SCRIPT_TABLE_PUSH_FUNCTION(getDistance);
    SCRIPT_TABLE_PUSH_FUNCTION(getSquareDistance);
    SCRIPT_TABLE_PUSH_FUNCTION(getAngle);
    SCRIPT_TABLE_PUSH_FUNCTION(getNormalized);
    SCRIPT_TABLE_PUSH_FUNCTION(getRotated);
}

void Vector2::push(lua_State * state, const Vector2 & value)
{
    lua_newtable(state);
    lua_pushnumber(state, value.x);
    lua_setfield(state, -2, "x");

    lua_pushnumber(state, value.y);
    lua_setfield(state, -2, "y");

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);
    lua_setmetatable(state, -2);
}

void Vector2::replace(lua_State * state, const Vector2 & value)
{
    lua_pushnumber(state, value.x);
    lua_setfield(state, -2, "x");

    lua_pushnumber(state, value.y);
    lua_setfield(state, -2, "y");
}

void Vector2::fill(lua_State * state, Vector2 & result, int position)
{
    lua_getfield(state, position, "x");
    result.x = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, position, "y");
    result.y = lua_tonumber(state, -1);
    lua_pop(state, 1);
}

void Vector2::fillTableSafe(lua_State * state, Vector2 & result, const char * name, int table_position, const Vector2 & default_value)
{
    lua_getfield(state, table_position, name);

    if(lua_isnil(state, -1))
    {
        result =  default_value;
    }
    else
    {
        Vector2::fill(state, result);
    }

    lua_pop(state, 1);
}

float Vector2::getLength(const Vector2 & a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

float Vector2::getSquareLength(const Vector2 & a)
{
    return (a.x*a.x + a.y*a.y);
}

float Vector2::getDistance(const Vector2 & a, const Vector2 & b)
{
    return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}

float Vector2::getSquareDistance(const Vector2 & a, const Vector2 & b)
{
    return (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
}

float Vector2::getAngle(const Vector2 & a, const Vector2 & b)
{
    return atan2(b.y - a.y, b.x - a.x);
}

int
    Vector2::metaTableRef;

Vector2 operator*(const Vector2 & vector, const float multiplier)
{
    return Vector2(vector.x * multiplier, vector.y * multiplier);
}

Vector2 operator-(const Vector2 & a, const Vector2 & b)
{
    return Vector2(a.x - b.x, a.y - b.y);
}

Vector2 operator+(const Vector2 & a, const Vector2 & b)
{
    return Vector2(a.x + b.x, a.y + b.y);
}

}
