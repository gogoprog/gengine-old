#include "script.h"

namespace gengine
{
namespace script
{

int getTableInteger(lua_State * state, const int position, const char * name, const int default_value)
{
    lua_getfield(state, position, name);

    if(lua_isnil(state, -1))
    {
        lua_pop(state, 1);
        return default_value;
    }

    return static_cast<int>(lua_tonumber(state, -1));
}

}
}

