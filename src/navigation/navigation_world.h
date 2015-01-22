#pragma once

#include "primitives.h"
#include "array.h"
#include "script.h"

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

private:

};

}
}
