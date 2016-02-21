#include "entity_component_custom.h"

#include "script_system.h"

namespace gengine
{
namespace entity
{

void ComponentCustom::init()
{
    scriptCall("init");
}

void ComponentCustom::finalize()
{

}

void ComponentCustom::insert()
{
    scriptCall("insert");
}

void ComponentCustom::update(const float dt)
{
    auto state = script::System::getInstance().getState();

    lua_rawgeti(state, LUA_REGISTRYINDEX, ref);
    lua_getfield(state, -1, "update");
    lua_rawgeti(state, LUA_REGISTRYINDEX, ref);
    script::push(state, dt);
    script::System::getInstance().call(2, 0);
    lua_pop(state, 1);
}

void ComponentCustom::remove()
{
    scriptCall("remove");
}

void ComponentCustom::scriptCall(const char *name)
{
    auto state = script::System::getInstance().getState();

    lua_rawgeti(state, LUA_REGISTRYINDEX, ref);
    lua_getfield(state, -1, name);
    lua_rawgeti(state, LUA_REGISTRYINDEX, ref);
    script::System::getInstance().call(1, 0);
    lua_pop(state, 1);
}

}
}
