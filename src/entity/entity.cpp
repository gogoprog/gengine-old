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

    luaL_dostring(state, "return function(self, comp, params) self.components[comp.name] = comp for k,v in pairs(params) do comp[k] = v end comp:init(params) rawset(comp,'entity',self) end");
    lua_setfield(state, -2, "addComponent");

    metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_setfield(state, -2, "__index");

    lua_pop(state, 1);
}

void fillTransform(lua_State *state, Transform & transform, const int position)
{
    lua_getfield(state, position, "position");
    script::fillVector2(state, transform.position);
    lua_pop(state, 1);

    lua_getfield(state, position, "rotation");
    transform.rotation = lua_tonumber(state, -1);
    lua_pop(state, 1);
}

void fillTransformFromComponent(lua_State *state, Transform & transform)
{
    lua_getfield(state, 1, "entity");
    fillTransform(state, transform);
    lua_pop(state, 1);
}

}
}
