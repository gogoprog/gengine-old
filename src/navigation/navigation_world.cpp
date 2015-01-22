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


    lua_settable(state, -3);
}

void World::update(const float dt)
{

}

}
}
