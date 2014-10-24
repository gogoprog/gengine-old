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