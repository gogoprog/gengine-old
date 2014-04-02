#pragma once

#include "primitives.h"
#include "array.h"
#include "vector2.h"
#include "script.h"
#include "debug.h"

namespace gengine
{
namespace entity
{

class System
{
public:
    struct Transform
    {
        Vector2
            position;
        float
            rotation;
    };

    SINGLETON(System);

    void init();
    void finalize();
    void update(const float dt);

    float getCurrentDt() const { return currentDt; }
    Transform & getCurrentTransform() { return currentTransform; }

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

private:

    template<typename COMPONENT>
    static void registerComponent(lua_State * state, const char * name, const char * attribute_name)
    {
        lua_newtable(state);

        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, insert);
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, init);
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, update);
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, remove);

        lua_pushcfunction(state, &COMPONENT::create);
        lua_setfield(state, -2, "__call");

        SCRIPT_TABLE_PUSH_STRING(name, attribute_name);

        COMPONENT::metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);
        lua_setmetatable(state, -2);

        lua_pushstring(state, "__newindex");
        lua_pushcfunction(state, &COMPONENT::newIndex);
        lua_rawset(state, -3);

        lua_pushstring(state, "__index");
        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);
        lua_rawset(state, -3);

        lua_setglobal(state, name);
    }

    static void pushTransform(lua_State * state, const Transform & transform);

    Array<int>
        refTable;
    Transform
        currentTransform;
    float
        currentDt;
};

}
}
