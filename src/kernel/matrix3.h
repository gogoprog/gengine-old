#pragma once

namespace gengine
{

class Matrix3
{
public:
    Matrix3();
    void setIdentity();
    void setTranslation(const float x, const float y);

    inline float get(const int x, const int y) const
    {
        return data[3*y + x];
    }

    inline float & get(const int x, const int y)
    {
        return data[3*y + x];
    }

protected:
    float data[9];
};

}
