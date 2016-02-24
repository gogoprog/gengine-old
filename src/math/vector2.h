#pragma once

#include "script.h"
#include "script_binder.h"
#include <Urho3D/Math/Vector2.h>

namespace gengine
{
namespace math
{
    typedef Urho3D::Vector2
        Vector2;
}

namespace script {
template<>
class Binder<math::Vector2>
{
public:

    static void get(script::State state, math::Vector2 & result, int position = -1)
    {
        result = * script::get<math::Vector2>(state, position);
    }

    static void push(script::State state, const math::Vector2 & value)
    {
        /*math::Vector2* tolua_obj = Mtolua_new(math::Vector2);
        tolua_pushusertype(state, tolua_obj, "Vector2");
        tolua_register_gc(state, lua_gettop(state));*/
    }

    static void update(script::State state, const math::Vector2 & value)
    {
        /*lua_pushnumber(state, value.x);
        lua_setfield(state, -2, "x");

        lua_pushnumber(state, value.y);
        lua_setfield(state, -2, "y");*/
    }
};
}

}
