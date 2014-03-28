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

SCRIPT_REGISTERER()
{
    System::getInstance().luaRegister(state);

    lua_newtable(state);

    luaL_dostring(state, "return function(self, dt) for k,v in pairs(self.components) do v:update(dt) end end");
    lua_setfield(state, -2, "update");

    luaL_dostring(state, "return function(self) for k,v in pairs(self.components) do v:insert() end end");
    lua_setfield(state, -2, "insert");

    luaL_dostring(state, "return function(self, comp, params) self.components[comp.name] = comp for k,v in pairs(params) do comp[k] = v end comp:init(params) end");
    lua_setfield(state, -2, "addComponent");

    metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_setfield(state, -2, "__index");

    lua_pop(state, 1);
}

}
}
