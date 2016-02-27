#pragma once

#include "primitives.h"
#include "array.h"
#include "maths.h"
#include "script.h"
#include "debug.h"

namespace gengine
{
namespace entity
{
class Entity;

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

    inline void readEntityTransform(script::State state, Entity & entity, const int position);
    inline void writeEntityTransform(script::State state, const Entity & entity, const int position);

private:

    template<typename COMPONENT>
    static void registerComponent(lua_State * state, const char *name)
    {
        lua_newtable(state);

        COMPONENT::luaRegister(state);

        lua_pushcfunction(state, &COMPONENT::_create);
        lua_setfield(state, -2, "__call");

        COMPONENT::metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);

        lua_rawgeti(state, LUA_REGISTRYINDEX, COMPONENT::metaTableRef);
        lua_setmetatable(state, -2);

        lua_pushstring(state, "__newindex");
        lua_pushcfunction(state, &COMPONENT::_newIndex);
        lua_rawset(state, -3);

        lua_pushstring(state, "__index");

        lua_pushcfunction(state, &System::componentIndex<COMPONENT>);

        lua_rawset(state, -3);

        lua_setglobal(state, name);
    }

    template<typename COMPONENT>
    static int componentIndex(lua_State * state)
    {
        if(COMPONENT::getterMap.contains(lua_tostring(state, 2)))
        {
            return COMPONENT::_index(state);
        }
        else
        {
            lua_getmetatable(state, 1);
            lua_pushvalue(state, 2);
            lua_rawget(state, -2);

            return 1;
        }
    }

    Array<Entity*>
        entities,
        entitiesToRemove,
        entitiesToUpdate;
    float
        currentDt;
};

}
}

#include "entity_entity.h"

namespace gengine
{
namespace entity
{

inline void System::readEntityTransform(script::State state, Entity & entity, const int position)
{
    lua_getfield(state, position, "position");
    lua_getfield(state, position < 0 ? position - 1 : position, "scale");
    lua_getfield(state, position < 0 ? position - 2 : position, "rotation");

    entity.node->SetTransform2D(
        *script::get<math::Vector2>(state, -3),
        lua_tonumber(state, -1),
        *script::get<math::Vector2>(state, -2)
        );

    lua_pop(state, 3);
}

inline void System::writeEntityTransform(script::State state, const Entity & entity, const int position)
{
    script::push(state, entity.node->GetPosition());
    lua_setfield(state, position - 1, "position");
}

}
}
