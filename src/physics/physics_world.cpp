#include "physics_world.h"

#include "debug.h"

#define FIXED_TIME_STEP 0.01

namespace gengine
{
namespace physics
{

struct AllResult : public b2RayCastCallback
{
    virtual float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &  point, const b2Vec2 &  normal, float32 fraction) override
    {
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

void World::update(const float dt)
{
    timeLeft += dt;

    while(timeLeft > FIXED_TIME_STEP)
    {
        b2world.Step(FIXED_TIME_STEP, 8, 3);

        timeLeft -= FIXED_TIME_STEP;
    }
}

}
}
