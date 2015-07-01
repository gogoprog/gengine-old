#include "entity_system.h"

#include "primitives.h"
#include "array.h"
#include "script.h"
#include "script_system.h"
#include "debug.h"
#include "vector2.h"
#include "string.h"
#include "entity.h"
#include "entity_component_sprite.h"
#include "entity_component_camera.h"
#include "entity_component_mouseable.h"
#include "entity_component_animated_sprite.h"
#include "entity_component_sprite_batch.h"
#include "entity_component_physic.h"
#include "entity_component_navigation_agent.h"
#include "entity_component_particle_system.h"
#include "entity_component_quad.h"
#include "entity_component_spriter.h"

namespace gengine
{
namespace entity
{

void System::init()
{
}

void System::finalize()
{
}

void System::update(const float dt)
{
    bool isInserted;
    lua_State * state = script::System::getInstance().getState();
    currentDt = dt;

    refToUpdateTable = refTable;

    for(int ref : refToUpdateTable)
    {
        lua_rawgeti(state, LUA_REGISTRYINDEX, ref);

        lua_getfield(state, -1, "_isInserted");
        isInserted = lua_toboolean(state, -1);
        lua_pop(state, 1);

        if(isInserted)
        {
            lua_getfield(state, -1, "update");
            lua_rawgeti(state, LUA_REGISTRYINDEX, ref);
            lua_pushnumber(state, dt);
            script::System::getInstance().call(2, 0);
        }

        lua_pop(state, 1);
    }

    if(refToRemoveTable.getSize() > 0 && refTable.getSize() > 0)
    {
        for(int i = int(refTable.getSize()) - 1; i >= 0; --i)
        {
            int ref = refTable[i];

            for(uint j = 0; j < refToRemoveTable.getSize(); ++j)
            {
                int refToRemove = refToRemoveTable[j];

                if(ref == refToRemove)
                {
                    luaL_unref(state, LUA_REGISTRYINDEX, ref);
                    refTable.removeAt(i);
                    refToRemoveTable.removeAt(j);
                    break;
                }
            }
        }
    }
}

SCRIPT_CLASS_REGISTERER(System)
{
    lua_newtable(state);

    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(System, getCount);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(System, create);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(System, destroy);

    SCRIPT_DO(
        return function(_table)
            _table.__call = function()
                local o = {}
                setmetatable(o, _table)
                return o
            end

            _table.__newindex = function(self,k,v)
                rawset(self,k,v)
            end

            _table.__index = function(_t, _key)
                return rawget(getmetatable(_t),_key)
            end

            setmetatable(_table, _table)
        end
        );

    lua_setfield(state, -2, "registerCustomComponent");

    lua_getglobal(state, "_G");
    lua_pushnil(state);

    while(lua_next(state, -2))
    {
        if(lua_type(state, -1) == LUA_TTABLE)
        {
            const char * name = lua_tostring(state, -2);

            if(!strncmp("Component", name, 9))
            {
                if(!lua_getmetatable(state, -1))
                {
                    lua_getfield(state, -4, "registerCustomComponent");

                    lua_getglobal(state, name);

                    lua_call(state, 1, 0);
                }
                else
                {
                    lua_pop(state, 1);
                }
            }
        }

        lua_pop(state, 1);
    }

    lua_pop(state, 1);

    lua_setfield(state, -2, "entity");

    registerComponent<ComponentSprite>(state, "ComponentSprite");
    registerComponent<ComponentCamera>(state, "ComponentCamera");
    registerComponent<ComponentMouseable>(state, "ComponentMouseable");
    registerComponent<ComponentAnimatedSprite>(state, "ComponentAnimatedSprite");
    registerComponent<ComponentSpriteBatch>(state, "ComponentSpriteBatch");
    registerComponent<ComponentPhysic>(state, "ComponentPhysic");
    registerComponent<ComponentNavigationAgent>(state, "ComponentNavigationAgent");
    registerComponent<ComponentParticleSystem>(state, "ComponentParticleSystem");
    registerComponent<ComponentQuad>(state, "ComponentQuad");
    registerComponent<ComponentSpriter>(state, "ComponentSpriter");
}

SCRIPT_CLASS_UNREGISTERER(System)
{
    // :todo: remove entities/components
}

SCRIPT_CLASS_FUNCTION(System, create)
{
    lua_newtable(state);

    SCRIPT_DO(
        return vector2()
        );

    lua_setfield(state, -2, "position");

    SCRIPT_TABLE_PUSH_NUMBER(rotation, 0);

    lua_newtable(state);
    lua_setfield(state, -2, "components");

    lua_rawgeti(state, LUA_REGISTRYINDEX, getMetaTableRef());
    lua_setmetatable(state, -2);

    int ref = luaL_ref(state, LUA_REGISTRYINDEX);

    getInstance().refTable.add(ref);

    lua_rawgeti(state, LUA_REGISTRYINDEX, ref);

    lua_pushnumber(state, ref);
    lua_setfield(state, -2, "_ref");

    return 1;
}

SCRIPT_CLASS_FUNCTION(System, getCount)
{
    lua_pushnumber(state, getInstance().refTable.getSize());

    return 1;
}

SCRIPT_CLASS_FUNCTION(System, destroy)
{
    lua_getfield(state, 1, "_ref");
    int ref = lua_tonumber(state, -1);
    lua_pop(state, 1);

    lua_pushboolean(state, true);
    lua_setfield(state, 1, "destroyed");

    getInstance().refToRemoveTable.add(ref);

    return 0;
}

void System::pushTransform(lua_State * state, const Transform & transform)
{
    lua_getfield(state, -1, "position");
    SCRIPT_TABLE_PUSH_NUMBER(x, transform.position.x);
    SCRIPT_TABLE_PUSH_NUMBER(y, transform.position.y);

    lua_pop(state, 1);

    SCRIPT_TABLE_PUSH_NUMBER(rotation, transform.rotation);
}


}
}
