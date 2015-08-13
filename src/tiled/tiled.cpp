#include "tiled.h"

#include "debug.h"

namespace gengine
{
namespace tiled
{

SCRIPT_FUNCTION(createEntities)
{
    geLog(":todo:")

    return 0;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_FUNCTION(createEntities);

    lua_setfield(state, -2, "tiled");
}

}
}
