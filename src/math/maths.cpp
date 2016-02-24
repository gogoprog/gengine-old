#include "kernel.h"

#include "script.h"
#include "vector2.h"
#include "vector4.h"

#define PI 3.14159265358979323846264338327950288419716939937510f
#define HALF_PI PI / 2
#define TWO_PI PI * 2

namespace gengine
{
namespace math
{
/*
float getClosestAngle(const float angle, const float other_angle)
{
    float lower_angle, upper_angle;
    float closest_angle = angle;

    lower_angle = other_angle - PI + 0.00001f;
    upper_angle = other_angle + PI;

    while(closest_angle > upper_angle)
    {
        closest_angle -= TWO_PI;
    }

    while(lower_angle > closest_angle)
    {
        closest_angle += TWO_PI;
    }

    return closest_angle;
}

SCRIPT_FUNCTION(getClosestAngle)
{
    float angle, other_angle;

    angle = lua_tonumber(state, 1);
    other_angle = lua_tonumber(state, 2);

    lua_pushnumber(state, getClosestAngle(angle, other_angle));

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

    script::get(state, position1, 1);
    script::get(state, half_extent1, 2);
    script::get(state, position2, 3);
    script::get(state, half_extent2, 4);

    half_extent1 *= 0.5f;
    half_extent2 *= 0.5f;

    result = !(
        (position1.x_ + half_extent1.x_ < position2.x_ - half_extent2.x_)
        || (position2.x_ + half_extent2.x_ < position1.x_ - half_extent1.x_)
        || (position1.y_ + half_extent1.y_ < position2.y_ - half_extent2.y_)
        || (position2.y_ + half_extent2.y_ < position1.y_ - half_extent1.y_)
        );

    lua_pushboolean(state, result);

    return 1;
}


SCRIPT_FUNCTION(doCirclesIntersect)
{
    Vector2
        position1,
        position2;
    float
        radius1,
        radius2;
    bool
        result;

    script::get(state, position1, 1);
    script::get(state, radius1, 2);
    script::get(state, position2, 3);
    script::get(state, radius2, 4);

    //result = Vector2::getDistance(position1, position2) < radius1 + radius2;

    lua_pushboolean(state, result);

    return 1;
}

SCRIPT_FUNCTION(doesCircleIntersectRectangle)
{
    Vector2
        circle_position,
        rect_position,
        half_extent,
        minimum_point,
        maximum_point;
    float
        radius,
        square_distance;
    bool
        result;

    script::get(state, circle_position, 1);
    radius = lua_tonumber(state, 2);
    script::get(state, rect_position, 3);
    script::get(state, half_extent, 4);

    half_extent *= 0.5f;

    minimum_point = rect_position - half_extent;
    maximum_point = rect_position + half_extent;

    square_distance = 0.0f;

    if(circle_position.x < minimum_point.x)
    {
        square_distance += (circle_position.x - minimum_point.x) * (circle_position.x - minimum_point.x);
    }
    else if(circle_position.x > maximum_point.x)
    {
        square_distance += (circle_position.x - maximum_point.x) * (circle_position.x - maximum_point.x);
    }

    if(circle_position.y < minimum_point.y)
    {
        square_distance += (circle_position.y - minimum_point.y) * (circle_position.y - minimum_point.y);
    }
    else if(circle_position.y > maximum_point.y)
    {
        square_distance += (circle_position.y - maximum_point.y) * (circle_position.y - maximum_point.y);
    }

    result = square_distance < radius * radius;

    lua_pushboolean(state, result);

    return 1;
}
*/
SCRIPT_REGISTERER()
{
    lua_newtable(state);

    //Vector2::luaRegister(state);
    Vector4::luaRegister(state);

    /*SCRIPT_TABLE_PUSH_FUNCTION(getClosestAngle);
    SCRIPT_TABLE_PUSH_FUNCTION(doRectanglesIntersect);
    SCRIPT_TABLE_PUSH_FUNCTION(doCirclesIntersect);
    SCRIPT_TABLE_PUSH_FUNCTION(doesCircleIntersectRectangle);*/

    lua_setfield(state, -2, "math");
}

}
}
