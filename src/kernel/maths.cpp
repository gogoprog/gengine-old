#include "kernel.h"

#include "script.h"
#include "vector2.h"
#include "vector4.h"

#define PI 3.14159265358979323846264338327950288419716939937510f
#define HALF_PI PI / 2
#define TWO_PI PI * 2

namespace gengine
{
namespace kernel
{
namespace math
{

SCRIPT_FUNCTION(getClosestAngle)
{
    float
        closest_angle,
        lower_angle,
        upper_angle,
        other_angle;

    closest_angle = lua_tonumber(state, 1);
    other_angle = lua_tonumber(state, 2);

    lower_angle = other_angle - PI + 0.00001f;
    upper_angle = other_angle + PI;

    while ( closest_angle > upper_angle )
    {
        closest_angle -= TWO_PI;
    }

    while ( lower_angle > closest_angle )
    {
        closest_angle += TWO_PI;
    }

    lua_pushnumber(state, closest_angle);

    return 1;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    Vector2::luaRegister(state);
    Vector4::luaRegister(state);

    SCRIPT_TABLE_PUSH_FUNCTION(getClosestAngle);

    lua_setfield(state, -2, "math");
}

}
}
}
