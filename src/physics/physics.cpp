#include "physics.h"

#include "physics_system.h"
#include "physics_world.h"

namespace gengine
{
namespace physics
{

SCRIPT_FUNCTION(createWorlds)
{
    uint count = lua_tonumber(state, 1);
    System::getInstance().createWorlds(count);

    lua_getglobal(state, "gengine");
    lua_getfield(state, -1, "physics");
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

    lua_setfield(state, -2, "physics");
}

}
}
