#pragma once

namespace gengine
{

struct Vector4
{
    Vector4() = default;
    Vector4(const float _x, const float _y, const float _z, const float _w);

    float x,y,z,w;
};

}