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

    SCRIPT_DO(
        _trick = {
            __call = function(o, e, ...)
                return _trick.func(_trick.comp, ...)
            end
        }
        setmetatable(_trick,_trick)
        );

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
            for k,v in ipairs(self.components) do
                v:insert()
            end
            self._isInserted = true
        end
        );

    lua_setfield(state, -2, "insert");

    SCRIPT_DO(
        return function(self)
            for k,v in ipairs(self.components) do
                v:remove()
            end
            self._isInserted = false
        end
        );

    lua_setfield(state, -2, "remove");

    SCRIPT_DO(
        return function(self)
            return self.isInserted == true
        end
        );

    lua_setfield(state, -2, "isInserted");

    SCRIPT_DO(
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

    metaTableRef = luaL_ref(state, LUA_REGISTRYINDEX);

    lua_rawgeti(state, LUA_REGISTRYINDEX, metaTableRef);

    SCRIPT_DO(
        return function(_t, _key)
            if type(_key) == "string" and _key:sub(1,2) == "on" then
                for k,v in ipairs(_t.components) do
                    if v[_key] ~= nil then
                        _trick.func = v[_key]
                        _trick.comp = v
                        return _trick
                    end
                end
            end
            return rawget(getmetatable(_t),_key)
        end
        );

    lua_setfield(state, -2, "__index");

    lua_pop(state, 1);
}

void fillTransform(lua_State *state, Transform & transform, const int position)
{
    lua_getfield(state, position, "position");
    Vector2::fill(state, transform.position);
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

void updateTransform(lua_State *state, const Transform & transform, const int position)
{
    lua_getfield(state, position, "position");
    Vector2::push(state, transform.position);
    lua_pop(state, 1);

    lua_pushnumber(state, transform.rotation);
    lua_setfield(state, -2, "rotation");
}

void updateTransformFromComponent(lua_State *state, const Transform & transform)
{
    lua_getfield(state, 1, "entity");
    updateTransform(state, transform);
    lua_pop(state, 1);
}

}
}
