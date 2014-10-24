#pragma once

#include "primitives.h"
#include "vector2.h"

namespace gengine
{

class Matrix3
{
public:
    void initIdentity();
    void initProjection(const Vector2 & extent, const Vector2 & translation = Vector2::zero);
    void setTranslation(const Vector2 & translation);
    void setRotation(const float angle);
    void preScale(const Vector2 & s);
    void scale(const Vector2 & s);

    inline float get(const int y, const int x) const
    {
        return data[3*y + x];
    }

    inline float & get(const int y, const int x)
    {
        return data[3*y + x];
    }

protected:
    float data[9];
};

}
