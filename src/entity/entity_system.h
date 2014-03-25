#pragma once

#include "primitives.h"
#include "array.h"
#include "script.h"
#include "vector2.h"

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
    void update(const float dt);

    float getCurrentDt() const { return currentDt; }
    Transform & getCurrentTransform() { return currentTransform; }

    SCRIPT_REGISTERER();

    template<typename COMPONENT>
    static int createComponent(lua_State * state)
    {
        COMPONENT * instance = new COMPONENT();

        lua_newtable(state);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);
        lua_setmetatable(state, -2);

        lua_pushlightuserdata(state, instance);
        lua_setfield(state, -2, "this");

        return 1;
    }

    static SCRIPT_FUNCTION(create);

private:

    template<typename COMPONENT>
    static void registerComponent(lua_State * state, const char * name, const char * attribute_name)
    {
        lua_newtable(state);

        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, insert);
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, update);
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(COMPONENT, remove);

        lua_pushcfunction(state, &COMPONENT::create);
        lua_setfield(state, -2, "__call");

        SCRIPT_TABLE_PUSH_STRING(name, attribute_name);

        COMPONENT::metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);
        lua_setmetatable(state, -2);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);
        lua_setfield(state, -2, "__index");

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
