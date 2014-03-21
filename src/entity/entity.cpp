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

SCRIPT_FUNCTION(metaIndex)
{
    const char *key = lua_tostring(state, 2);

    if(!strcmp(key,"update"))
    {

    }

    return 0;
}

SCRIPT_REGISTERER()
{
    System::getInstance().luaRegister(state);

    lua_newtable(state);

    lua_pushcfunction(state, &metaIndex);
    lua_setfield(state, -2, "__index");

    metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);
}

}
}
