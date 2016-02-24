#include "physics_world.h"

#include "debug.h"
#include "vector2.h"
#include "script_system.h"
#include "entity_entity.h"

#define FIXED_TIME_STEP 0.01

namespace gengine
{

using namespace math;

namespace physics
{

struct LocalAllResult : public b2RayCastCallback
{
    Array<entity::Entity*>
        entities;

    virtual float32 ReportFixture(b2Fixture *fixture, const b2Vec2 & point, const b2Vec2 &  normal, float32 fraction) override
    {
        entities.add(reinterpret_cast<entity::Entity*>(fixture->GetUserData()));
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

    Vector2 *gravity = script::get<Vector2>(state, 2);

    self.b2world.SetGravity(b2Vec2(gravity->x_, gravity->y_));

    return 0;
}

SCRIPT_CLASS_FUNCTION(World, rayCast)
{
    SCRIPT_GET_SELF(World);
/*
    LocalAllResult results;

    Vector2 *start = script::get<Vector2>(state, 2);
    Vector2 *end = script::get<Vector2>(state, 2);

    script::get(state, start, 2);
    script::get(state, end, 3);

    self.b2world.RayCast(&results, b2Vec2(start->x_, start.y_), b2Vec2(end.x_, end.y_));

    for(auto entity : results.entities)
    {
        lua_pushvalue(state, 4);
        lua_rawgeti(state, LUA_REGISTRYINDEX, entity->getRef());

        script::System::getInstance().call(1, 0);
    }
*/
    return 0;
}

}
}
