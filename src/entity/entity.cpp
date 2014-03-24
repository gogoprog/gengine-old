#include "entity.h"

#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include "string.h"

namespace gengine
{
namespace entity
{

int
    metaTableRef;

int getMetaTableRef() { return metaTableRef; }

SCRIPT_FUNCTION(update)
{
    geLog("oui");

    return 0;
}

SCRIPT_FUNCTION(addComponent)
{
    lua_gettable(state, 1);

    lua_getfield(state, -1, "components");

    /*lua_gettable(state, 2);

    lua_setfield(state, -2, "test");*/

    lua_pop(state, 2);

    return 0;
}


SCRIPT_REGISTERER()
{
    System::getInstance().luaRegister(state);

    lua_newtable(state);

    lua_pushcfunction(state, &update);
    lua_setfield(state, -2, "update");

    lua_pushcfunction(state, &addComponent);
    lua_setfield(state, -2, "addComponent");

    metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_setfield(state, -2, "__index");

    lua_pop(state, 1);
}

}
}
