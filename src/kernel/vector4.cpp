#include "vector4.h"

#include "script.h"

namespace gengine
{

Vector4::Vector4(const float _x, const float _y, const float _z, const float _w)
    :
    x(_x),
    y(_y),
    z(_z),
    w(_w)
{
}

Vector4
    Vector4::zero(0.0f, 0.0f, 0.0f, 0.0f),
    Vector4::one(1.0f, 1.0f, 1.0f, 1.0f);

SCRIPT_CLASS_REGISTERER(Vector4)
{
    SCRIPT_DO(
        vector4_mt = {
            __tostring = function(t)
                return "(" .. string.format("%0.2f", t.x) .. ", " .. string.format("%0.2f", t.y) .. ", " .. string.format("%0.2f", t.z) .. ", " .. string.format("%0.2f", t.w) .. ")"
            end,
            __index = {
                set = function(t, x, y, z, w)
                    if type(x) == "number" then
                        t.x = x
                        t.y = y
                        t.z = z
                        t.w = w
                    elseif x.x == nil then
                        t.x = x[1]
                        t.y = x[2]
                        t.z = x[3]
                        t.w = x[4]
                    else
                        t.x = x.x
                        t.y = x.y
                        t.z = x.z
                        t.w = x.w
                    end
                end
            },
            __unm = function(t)
                return vector4(-t.x, -t.y, -t.z, -t.w)
            end,
            __add = function(a, b)
                return vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w)
            end,
            __sub = function(a, b)
                return vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w)
            end,
            __mul = function(a, b)
                return vector4(a.x * b, a.y * b, a.w * b, a.z * b)
            end,
            __div = function(a, b)
                return vector4(a.x / b, a.y / b, a.w / b, a.z / b)
            end
        }

        function vector4(_x, _y, _z, _w)
            local r = {x=_x or 0, y=_y or 0, z=_z or 0, w=_w or 0}
            setmetatable(r, vector4_mt)
            return r
        end
        );
}

void Vector4::fill(lua_State * state, Vector4 & result, int position)
{
    lua_getfield(state, position, "x");
    result.x = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, position, "y");
    result.y = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, position, "z");
    result.z = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, position, "w");
    result.w = lua_tonumber(state, -1);
    lua_pop(state, 1);
}

void Vector4::fillTableSafe(lua_State * state, Vector4 & result, const char * name, int table_position, const Vector4 & default_value)
{
    lua_getfield(state, table_position, name);

    if(lua_isnil(state, -1))
    {
        result =  default_value;
    }
    else
    {
        Vector4::fill(state, result);
    }

    lua_pop(state, 1);
}

}