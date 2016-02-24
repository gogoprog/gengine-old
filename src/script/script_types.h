#pragma once

#include "script_lua.h"

namespace gengine
{
namespace script
{

template<class T>
T *get(lua_State * state, const int position = -1)
{
    return (T*)tolua_tousertype(state, position, 0);
}

}
}
