#include "kernel.h"

#include "script.h"
#include "vector4.h"
#include "maths.h"

#define PI 3.14159265358979323846264338327950288419716939937510f
#define HALF_PI PI / 2
#define TWO_PI PI * 2

namespace gengine
{
namespace math
{

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

    position1 = * script::get<Vector2>(state, 1);
    half_extent1 = * script::get<Vector2>(state, 2);
    position2 = * script::get<Vector2>(state, 3);
    half_extent2 = * script::get<Vector2>(state, 4);

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

    position1 = * script::get<Vector2>(state, 1);
    script::get(state, radius1, 2);
    position2 = * script::get<Vector2>(state, 3);
    script::get(state, radius2, 4);

    result = (position1 - position2).Length() < radius1 + radius2;

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

    circle_position = * script::get<Vector2>(state,  1);
    radius = lua_tonumber(state, 2);
    rect_position = * script::get<Vector2>(state,  3);
    half_extent = * script::get<Vector2>(state,  4);

    half_extent *= 0.5f;

    minimum_point = rect_position - half_extent;
    maximum_point = rect_position + half_extent;

    square_distance = 0.0f;

    if(circle_position.x_ < minimum_point.x_)
    {
        square_distance += (circle_position.x_ - minimum_point.x_) * (circle_position.x_ - minimum_point.x_);
    }
    else if(circle_position.x_ > maximum_point.x_)
    {
        square_distance += (circle_position.x_ - maximum_point.x_) * (circle_position.x_ - maximum_point.x_);
    }

    if(circle_position.y_ < minimum_point.y_)
    {
        square_distance += (circle_position.y_ - minimum_point.y_) * (circle_position.y_ - minimum_point.y_);
    }
    else if(circle_position.y_ > maximum_point.y_)
    {
        square_distance += (circle_position.y_ - maximum_point.y_) * (circle_position.y_ - maximum_point.y_);
    }

    result = square_distance < radius * radius;

    lua_pushboolean(state, result);

    return 1;
}

SCRIPT_REGISTERER()
{
    lua_newtable(state);

    Vector4::luaRegister(state);

    SCRIPT_TABLE_PUSH_FUNCTION(getClosestAngle);
    SCRIPT_TABLE_PUSH_FUNCTION(doRectanglesIntersect);
    SCRIPT_TABLE_PUSH_FUNCTION(doCirclesIntersect);
    SCRIPT_TABLE_PUSH_FUNCTION(doesCircleIntersectRectangle);

    lua_setfield(state, -2, "math");
}

}
}
