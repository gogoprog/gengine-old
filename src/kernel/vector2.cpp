#include "vector2.h"

namespace gengine
{

Vector2::Vector2(const float _x, const float _y)
    :
    x(_x),
    y(_y)
{
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
                    else
                        t.x = x[1]
                        t.y = x[2]
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
            end
        }

        function vector2(_x, _y)
            local r = {x=_x or 0, y=_y or 0}
            setmetatable(r, vector2_mt)
            return r
        end
        );
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

Vector2 operator*(const Vector2 & vector, const float multiplier)
{
    return Vector2(vector.x * multiplier, vector.y * multiplier);
}


}
