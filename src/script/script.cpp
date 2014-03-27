#include "script.h"

#include "vector2.h"

namespace gengine
{
namespace script
{

void fillVector2(lua_State * state, Vector2 & result, int position)
{
    lua_getfield(state, -1, "x");
    result.x = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "y");
    result.y = lua_tonumber(state, -1);
    lua_pop(state, 1);
}

void fillTableVector2Safe(lua_State * state, Vector2 & result, const char * name, int table_position, const Vector2 default_value)
{
    lua_getfield(state, table_position, name);

    if(lua_isnil(state, -1))
    {
        result =  default_value;
    }
    else
    {
        fillVector2(state, result);
    }

    lua_pop(state, 1);
}

void fillVector4(lua_State * state, Vector4 & result, int position)
{
    lua_getfield(state, -1, "x");
    result.x = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "y");
    result.y = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "z");
    result.z = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "w");
    result.w = lua_tonumber(state, -1);
    lua_pop(state, 1);
}

void fillTableVector4Safe(lua_State * state, Vector4 & result, const char * name, int table_position, const Vector4 default_value)
{
    lua_getfield(state, table_position, name);

    if(lua_isnil(state, -1))
    {
        result =  default_value;
    }
    else
    {
        fillVector4(state, result);
    }

    lua_pop(state, 1);
}

int getTableInteger(lua_State * state, const char * name, const int table_position)
{
    int result;

    lua_getfield(state, table_position, name);

    result = static_cast<int>(lua_tonumber(state, -1));

    lua_pop(state, 1);

    return result;
}

int getTableIntegerSafe(lua_State * state, const char * name, const int table_position, const int default_value)
{
    int result;

    lua_getfield(state, table_position, name);

    if(lua_isnil(state, -1))
    {
        result =  default_value;
    }
    else
    {
        result = static_cast<int>(lua_tonumber(state, -1));
    }

    lua_pop(state, 1);

    return result;
}

float getTableFloat(lua_State * state, const char * name, const int table_position)
{
    float result;

    lua_getfield(state, table_position, name);

    result = static_cast<float>(lua_tonumber(state, -1));

    lua_pop(state, 1);

    return result;
}

float getTableFloatSafe(lua_State * state, const char * name, const int table_position, const float default_value)
{
    float result;

    lua_getfield(state, table_position, name);

    if(lua_isnil(state, -1))
    {
        result =  default_value;
    }
    else
    {
        result = static_cast<float>(lua_tonumber(state, -1));
    }

    lua_pop(state, 1);

    return result;
}

}
}

