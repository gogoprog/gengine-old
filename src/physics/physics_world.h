#pragma once

#include "primitives.h"
#include "array.h"
#include "Box2D/Box2D.h"

namespace gengine
{
namespace physics
{

class World
{
public:
    World();
    ~World();

    void update(const float dt);

    b2World & getBox2dWorld() { return b2world; }

private:
    b2World
        b2world;
    float
        timeLeft;
};

}
}
