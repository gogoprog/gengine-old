#include "physics_world.h"

#include "debug.h"
#include "vector2.h"
#include "script_system.h"

#define FIXED_TIME_STEP 0.01

namespace gengine
{

using namespace math;

namespace physics
{

struct LocalAllResult : public b2RayCastCallback
{
    Array<int>
        entityRefTable;

    virtual float32 ReportFixture(b2Fixture *fixture, const b2Vec2 & point, const b2Vec2 &  normal, float32 fraction) override
    {
        entityRefTable.add(int(reinterpret_cast<long>(fixture->GetUserData())));
        return 0;
    }
};

World::World()
    :
    b2world(b2Vec2(0.0f, -100.0f)),
    timeLeft(0.0f)
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

    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(World, setGravity);
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(World, rayCast);

    lua_settable(state, -3);
}

void World::update(const float dt)
{
    timeLeft += dt;

    while(timeLeft > FIXED_TIME_STEP)
    {
        b2world.Step(FIXED_TIME_STEP, 8, 3);

        timeLeft -= FIXED_TIME_STEP;
    }
}

SCRIPT_CLASS_FUNCTION(World, setGravity)
{
    SCRIPT_GET_SELF(World);

    Vector2 gravity;

    script::Binder<Vector2>::get(state, gravity, 2);

    self.b2world.SetGravity(b2Vec2(gravity.x, gravity.y));

    return 0;
}

SCRIPT_CLASS_FUNCTION(World, rayCast)
{
    SCRIPT_GET_SELF(World);

    Vector2 start, end;
    LocalAllResult results;

    script::Binder<Vector2>::get(state, start, 2);
    script::Binder<Vector2>::get(state, end, 3);

    self.b2world.RayCast(&results, b2Vec2(start.x, start.y), b2Vec2(end.x, end.y));

    lua_pushvalue(state, 4);

    for(int ref : results.entityRefTable)
    {
        lua_pushvalue(state, 4);
        lua_rawgeti(state, LUA_REGISTRYINDEX, ref);

        script::System::getInstance().call(1, 0);
    }

    return 0;
}

}
}
