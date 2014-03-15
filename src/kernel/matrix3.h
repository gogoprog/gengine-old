#pragma once

namespace gengine
{

class Matrix3
{
public:
    void initIdentity();
    void initProjection(const float width, const float height, const float tx = 0.0f, const float ty = 0.0f);
    void setTranslation(const float x, const float y);
    void setRotation(const float angle);
    void preScale(const float sx, const float sy);
    void scale(const float sx, const float sy);

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
