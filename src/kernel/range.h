#pragma once

#include <cmath>
#include <cstdlib>

namespace gengine
{

template<class T>
struct Range
{
    Range() = default;

    Range(const T & min, const T & max) : minimum(min), maximum(max)
    {
    }

    T getRandom() const
    {
        return minimum + (maximum - minimum) * (std::rand()/ static_cast<float>(RAND_MAX));
    }

    void set(const T & min, const T & max)
    {
        minimum = min;
        maximum = max;
    }

    T
        minimum,
        maximum;
};

}
