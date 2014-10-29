#include "physics.h"

#include "physics_system.h"

namespace gengine
{
namespace physics
{

SCRIPT_FUNCTION(createWorlds)
{
    System::getInstance().createWorlds(lua_tonumber(state, 1));

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_FUNCTION(createWorlds);

    lua_setfield(state, -2, "physics");
}

}
}
