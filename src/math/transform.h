#pragma once

#include "primitives.h"
#include "vector2.h"
#include "script.h"

namespace gengine
{
namespace math
{

struct Transform
{
    Vector2
        position,
        scale;
    float
        rotation;
};

}

namespace script {
template<>
class Binder<math::Transform>
{
public:
    static void push(script::State state, const math::Transform & transform)
    {
        lua_newtable(state);

        script::push(state, transform.position);
        lua_setfield(state, -2, "position");

        script::push(state, transform.scale);
        lua_setfield(state, -2, "scale");

        script::push(state, transform.rotation);
        lua_setfield(state, -2, "rotation");
    }

    static void update(script::State state, const math::Transform & transform, int position = -1)
    {
        lua_getfield(state, position, "position");
        script::update(state, transform.position);
        lua_pop(state, 1);

        lua_getfield(state, position, "scale");
        script::update(state, transform.scale);
        lua_pop(state, 1);

        lua_pushnumber(state, transform.rotation);
        lua_setfield(state, position - 1, "rotation");
    }

    static void get(script::State state, math::Transform & transform, int position = -1)
    {
        lua_getfield(state, position, "position");
        script::get(state, transform.position);
        lua_pop(state, 1);

        lua_getfield(state, position, "scale");
        script::get(state, transform.scale);
        lua_pop(state, 1);

        lua_getfield(state, position, "rotation");
        script::get(state, transform.rotation);
        lua_pop(state, 1);
    }
};
}

}
