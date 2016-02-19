#include "entity.h"

#include "script.h"
#include "debug.h"
#include "string.h"
#include "entity_system.h"
#include "entity_component.h"

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

    lua_getfield(state, 2, "this");
    auto instance = reinterpret_cast<Component*>(lua_touserdata(state, -1));
    lua_pop(state, 1);

    if(name)
    {
        lua_pushvalue(state, 2);
        lua_setfield(state, 1, name);
    }

    lua_pushvalue(state, 1);
    lua_setfield(state, 2, "entity");

    lua_pushvalue(state, 4);
    lua_setfield(state, 2, "name");

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

    instance->init();

    return 0;
}

SCRIPT_REGISTERER()
{
    System::getInstance().luaRegister(state);

    lua_newtable(state);

    SCRIPT_DO(
        return function(self, dt)
            for k,v in ipairs(self.components) do
                v:update(dt)
            end
        end
        );

    lua_setfield(state, -2, "update");

    SCRIPT_DO(
        return function(self)
            if not self._isInserted then
                for k,v in ipairs(self.components) do
                    v:insert()
                end
                self._isInserted = true
            end
        end
        );

    lua_setfield(state, -2, "insert");

    SCRIPT_DO(
        return function(self)
            if self._isInserted then
                for k,v in ipairs(self.components) do
                    v:remove()
                end
                self._isInserted = false
            end
        end
        );

    lua_setfield(state, -2, "remove");

    SCRIPT_DO(
        return function(self)
            return self._isInserted == true
        end
        );

    lua_setfield(state, -2, "isInserted");

    /*SCRIPT_DO(
        return function(self, comp, params, name)
            if name ~= nil then
                self[name] = comp
            end
            rawset(comp, 'entity', self)
            rawset(comp, 'name', name)
            table.insert(self.components, comp)
            if params ~= nil then
                for k,v in pairs(params) do
                    comp[k] = v
                end
            end
            comp:init(params)
        end
        );

    lua_setfield(state, -2, "addComponent");
    */

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
