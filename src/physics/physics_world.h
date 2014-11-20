#pragma once

#include "primitives.h"
#include "array.h"
#include "Box2D/Box2D.h"
#include "script.h"

namespace gengine
{
namespace physics
{

class World
{
public:
    World();
    ~World();

    void luaRegister(lua_State * state, const uint index) const;

    void update(const float dt);

    b2World & getBox2dWorld() { return b2world; }

    static SCRIPT_FUNCTION(setGravity);

private:
    b2World
        b2world;
    float
        timeLeft;
};

}
}
