#include "entity_component_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "script.h"
#include "debug.h"

namespace gengine
{
namespace entity
{

SCRIPT_CLASS_REGISTERER(ComponentSprite)
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(ComponentSprite, insert);

    lua_pushcfunction(state, &ComponentSprite::create);
    lua_setfield(state, -2, "__call");

    metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);
    lua_setmetatable(state, -2);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);
    lua_setfield(state, -2, "__index");

    lua_setglobal(state, "ComponentSprite");
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, create)
{
    ComponentSprite * instance = new ComponentSprite();

    lua_newtable(state);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);
    lua_setmetatable(state, -2);

    lua_pushlightuserdata(state, instance);
    lua_setfield(state, -2, "this");

    return 1;
}

SCRIPT_CLASS_FUNCTION(ComponentSprite, insert)
{
    SCRIPT_GET_SELF(ComponentSprite);

    geLog("insert ok");

    (void)self;
    
    return 0;
}

uint ComponentSprite::metaTableRef;

}
}
