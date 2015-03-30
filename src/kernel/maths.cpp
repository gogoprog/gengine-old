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

SCRIPT_FUNCTION(doRectanglesIntersect)
{
    Vector2
        position1,
        position2,
        half_extent1,
        half_extent2;
    bool
        result;

    Vector2::fill(state, position1, 1);
    Vector2::fill(state, half_extent1, 2);
    Vector2::fill(state, position2, 3);
    Vector2::fill(state, half_extent2, 4);

    half_extent1 *= 0.5f;
    half_extent2 *= 0.5f;

    result = !(
        (position1.x + half_extent1.x < position2.x - half_extent2.x)
        || (position2.x + half_extent2.x < position1.x - half_extent1.x)
        || (position1.y + half_extent1.y < position2.y - half_extent2.y)
        || (position2.y + half_extent2.y < position1.y - half_extent1.y)
        );

    lua_pushboolean(state, result);

    return 1;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    Vector2::luaRegister(state);
    Vector4::luaRegister(state);

    SCRIPT_TABLE_PUSH_FUNCTION(getClosestAngle);
    SCRIPT_TABLE_PUSH_FUNCTION(doRectanglesIntersect);

    lua_setfield(state, -2, "math");
}

}
}
}
