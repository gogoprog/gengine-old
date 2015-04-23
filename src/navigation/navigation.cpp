#include "navigation.h"

#include "navigation_system.h"
#include "navigation_world.h"

namespace gengine
{
namespace navigation
{

SCRIPT_FUNCTION(createWorlds)
{
    uint count = lua_tonumber(state, 1);
    System::getInstance().createWorlds(count);

    lua_getglobal(state, "gengine");
    lua_getfield(state, -1, "navigation");
    lua_getfield(state, -1, "worlds");

    for(uint index=0; index < count; ++index)
    {
        System::getInstance().getWorld(index).luaRegister(state, index + 1);
    }

    lua_pop(state, 3);

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    lua_newtable(state);
    lua_setfield(state, -2, "worlds");

    SCRIPT_TABLE_PUSH_FUNCTION(createWorlds);

    SCRIPT_DO(
        return function(t, i) return t.worlds[i] end
        );

    lua_setfield(state, -2, "getWorld");

    lua_setfield(state, -2, "navigation");
}

}
}
