#pragma once

#include "primitives.h"
#include "array.h"
#include "script.h"
#include "tilemover2d.h"

namespace gengine
{
namespace navigation
{

class World
{
public:
    World();
    ~World();

    void luaRegister(lua_State * state, const uint index) const;

    void update(const float dt);

    tilemover2d::World & getWorld() { return world; }

    static SCRIPT_FUNCTION(init);
    static SCRIPT_FUNCTION(setTileBlocking);

private:
    tilemover2d::World
        world;
};

}
}
