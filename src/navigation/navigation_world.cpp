#include "navigation_world.h"

#include "debug.h"
#include "vector2.h"
#include "script_system.h"

#define FIXED_TIME_STEP 0.01

namespace gengine
{
namespace navigation
{

World::World()
{
}

World::~World()
{
}

void World::luaRegister(lua_State * state, const uint index) const
{
    lua_pushnumber(state, index);
    lua_newtable(state);
    SCRIPT_TABLE_PUSH_THIS();

    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(World, init);

    lua_settable(state, -3);
}

void World::update(const float dt)
{
    world.update(dt);
}

SCRIPT_CLASS_FUNCTION(World, init)
{
    SCRIPT_GET_SELF(World);

    uint w, h, tw, th;

    w = lua_tonumber(state, 2);
    h = lua_tonumber(state, 3);
    tw = lua_tonumber(state, 4);
    th = lua_tonumber(state, 5);

    self.world.init(w, h, tw, th);

    return 0;
}

SCRIPT_CLASS_FUNCTION(World, setTileBlocking)
{
    SCRIPT_GET_SELF(World);

    uint x, y;
    bool blocking_state;

    x = lua_tonumber(state, 2);
    y = lua_tonumber(state, 3);
    blocking_state = lua_toboolean(state, 4);

    self.world.setTileBlocking(x, y, blocking_state);

    return 0;
}

}
}
