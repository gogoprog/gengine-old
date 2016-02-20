#include "entity.h"

#include "script.h"
#include "debug.h"
#include "string.h"
#include "entity_system.h"
#include "entity_component.h"
#include "entity_entity.h"

namespace gengine
{

using namespace math;

namespace entity
{

int
    metaTableRef;

int getMetaTableRef() { return metaTableRef; }

SCRIPT_FUNCTION(addComponent)
{
    auto name = lua_tostring(state, 4);

    lua_getfield(state, 1, "_e");
    auto & entity_instance = * reinterpret_cast<Entity*>(lua_touserdata(state, -1));
    lua_pop(state, 1);

    lua_getfield(state, 2, "this");
    auto & component_instance = * reinterpret_cast<Component*>(lua_touserdata(state, -1));
    lua_pop(state, 1);

    if(name)
    {
        lua_pushstring(state, name);
        lua_pushvalue(state, 2);
        lua_rawset(state, 1);
    }

    lua_pushstring(state, "entity");
    lua_pushvalue(state, 1);
    lua_rawset(state, 2);

    lua_pushstring(state, "name");
    lua_pushvalue(state, 4);
    lua_rawset(state, 2);

    lua_pushvalue(state, 3);
    lua_pushnil(state);

    while(lua_next(state, -2))
    {
        auto key = lua_tostring(state, -2);
        lua_pushvalue(state, -1);
        lua_setfield(state, 2, key);
        lua_pop(state, 1);
    }

    lua_pop(state, 1);

    component_instance.init();
    component_instance.setEntity(entity_instance);

    entity_instance.addComponent(component_instance);

    return 0;
}

SCRIPT_REGISTERER()
{
    System::getInstance().luaRegister(state);

    lua_newtable(state);

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        insert,
        {
            lua_getfield(state, 1, "_e");
            auto & entity_instance = * reinterpret_cast<Entity*>(lua_touserdata(state, -1));
            lua_pop(state, 1);

            script::get(state, entity_instance.transform, 1);

            entity_instance.insert();

            return 0;
        });

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        remove,
        {
            lua_getfield(state, 1, "_e");
            auto & entity_instance = * reinterpret_cast<Entity*>(lua_touserdata(state, -1));
            lua_pop(state, 1);

            entity_instance.remove();

            return 0;
        });

    SCRIPT_TABLE_PUSH_INLINE_FUNCTION(
        isInserted,
        {
            lua_getfield(state, 1, "_e");
            auto & entity_instance = * reinterpret_cast<Entity*>(lua_touserdata(state, -1));
            lua_pop(state, 1);

            lua_pushboolean(state, entity_instance.isInserted());

            return 1;
        });

    SCRIPT_TABLE_PUSH_FUNCTION(addComponent);

    SCRIPT_DO(
        return function(self, name)
            for k, v in ipairs(self.components) do
                if v.name == name then
                    table.remove(self.components, k)
                    break
                end
            end

            self[name] = nil
        end
        );

    lua_setfield(state, -2, "removeComponent");

    SCRIPT_DO(
        return function(self, event_name, ...)
            local name = "on" .. event_name
            local result = 0
            for k, v in ipairs(self.components) do
                if v[name] and type(v[name]) == "function" then
                    v[name](v, ...)
                    result = result + 1
                end
            end

            if self[name] and type(self[name]) == "function" then
                self[name](self, ...)
                result = result + 1
            end

            return result
        end
        );

    lua_setfield(state, -2, "fireEvent");

    metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    lua_setfield(state, -2, "__index");

    lua_pop(state, 1);
}

void getTransformFromComponent(lua_State *state, math::Transform & transform)
{
    lua_getfield(state, 1, "entity");
    script::get(state, transform);
    lua_pop(state, 1);
}

void updateTransformFromComponent(lua_State *state, const math::Transform & transform)
{
    lua_getfield(state, 1, "entity");
    script::update(state, transform);
    lua_pop(state, 1);
}

}
}
