#pragma once

#include "primitives.h"
#include "array.h"
#include "vector2.h"
#include "script.h"
#include "debug.h"
#include "entity_transform.h"

namespace gengine
{
namespace entity
{

class System
{
public:

    SINGLETON(System);

    void init();
    void finalize();
    void update(const float dt);

    float getCurrentDt() const { return currentDt; }

    SCRIPT_REGISTERER();
    SCRIPT_UNREGISTERER();

    template<typename COMPONENT>
    static int createComponent(lua_State * state)
    {
        COMPONENT * instance = new COMPONENT();

        lua_newtable(state);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);
        lua_setmetatable(state, -2);

        lua_pushstring(state, "this");
        lua_pushlightuserdata(state, instance);
        lua_rawset(state, -3);

        return 1;
    }

    static SCRIPT_FUNCTION(create);
    static SCRIPT_FUNCTION(getCount);
    static SCRIPT_FUNCTION(destroy);

private:

    template<typename COMPONENT>
    static void registerComponent(lua_State * state, const char * name)
    {
        lua_newtable(state);

        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, init);

        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, insert);
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, update);
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, remove);

        COMPONENT::luaRegister(state);

        lua_pushcfunction(state, &COMPONENT::create);
        lua_setfield(state, -2, "__call");

        COMPONENT::metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);
        lua_setmetatable(state, -2);

        lua_pushstring(state, "__newindex");
        lua_pushcfunction(state, &COMPONENT::newIndex);
        lua_rawset(state, -3);

        lua_pushstring(state, "__index");

        SCRIPT_DO(
            return function(_t, _key)
                return rawget(getmetatable(_t),_key)
            end
            );

        lua_rawset(state, -3);

        lua_setglobal(state, name);
    }

    static void pushTransform(lua_State * state, const Transform & transform);

    Array<int>
        refTable,
        refToRemoveTable,
        refToUpdateTable;
    float
        currentDt;
};

}
}
